/**
 * MPLABX IDE project example for testing PIC18F4520 Development Board
 * 
 * @author   Burak Enez
 * @email    burakenez@gmail.com
 * @website  http://burakenez.org
 * @ide      MPLAB X IDE
 * @compiler XC8
 * @license  GNU GPL v3
 */

/* Include core modules */
#include <xc.h>
#include <stdio.h> //for printf()
#include <stdlib.h>
/* Include plibs here */
#include <plib/adc.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"
#include "pic18f4520_hd44780.h"
#include "pic18f4520_sseg.h"
#include "pic18f4520_keypad.h"

#define STATE_LCD       0
#define STATE_LED       1
#define STATE_SSEG      2
#define STATE_KEYPAD    3
#define STATE_ADC       4

/* KEY1 */
#define TRIS_KEY1   TRISBbits.RB0
#define PORT_KEY1   PORTBbits.RB0
/* KEY2 */
#define TRIS_KEY2   TRISBbits.RB1
#define PORT_KEY2   PORTBbits.RB1
/* LED1 */
#define TRIS_LED1   TRISCbits.RC1
#define LAT_LED1    LATCbits.LATC1
/* LED2 */
#define TRIS_LED2   TRISCbits.RC2
#define LAT_LED2    LATCbits.LATC2

int state = 0;
unsigned int sseg_counter = 0;
int int_key = 0xFF;
char char_key;
int adcin;
double dcf = 0; /* Average filter */
double dcf_old = 0; /* For better LCD performance */
double lamda = 0.05; /* Average of last 20 ADC read */

int adc_flag = 0;
int keypad_flag = 0;
int sseg_flag = 0;
int led_flag = 0;
int lcd_flag = 0;


int counter = 0;

int main(void) {
    TRIS_KEY1 = 1;
    TRIS_KEY2 = 1;
    TRIS_LED1 = 0;
    TRIS_LED2 = 0;
    LAT_LED1 = 0;
    LAT_LED2 = 0;

    /* External Interrupts Configuration */
    INTCONbits.INT0E = 1; /* Enable Interrupt 0 (RB0 as interrupt) */
    INTCON2bits.INTEDG0 = 1; /* Cause Interrupt 0 at rising edge */
    INTCONbits.INT0F = 0; /* Clear Interrupt 0 flag */
    INTCON3bits.INT1E = 1; /* Enable Interrupt 1 (RB1 as interrupt) */
    INTCON2bits.INTEDG1 = 1; /* Cause Interrupt 1 at rising edge */
    INTCON3bits.INT1F = 0; /* Clear Interrupt 0 flag */
    ei(); /* Global Interrupt Enable */

    /* Initialize LCD 16 cols x 2 rows */
    HD44780_Init(16, 2);
    HD44780_Puts(3, 0, "PIC18F4520");
    HD44780_Puts(0, 1, "16x2 HD44780 LCD");
    Delayms(2000);
    
    SSEG_Init();
    KEYPAD_Init();
    
    OpenADC(ADC_FOSC_4 &
            ADC_RIGHT_JUST &
            ADC_0_TAD,
            ADC_CH0 &
            ADC_REF_VDD_VSS &
            ADC_INT_OFF,
            ADC_1ANA);
    Delay(50);
    
    /* Loop forever */
    while(1) {
        if (state == STATE_LCD) {
            counter = 0;
            lcd_flag = 0;
            while(lcd_flag == 0) {
                HD44780_Clear();
                Delayms(250);
                HD44780_Clear();
                HD44780_Puts(0, 0, "1.LCD TEST");
                HD44780_Puts(0, 1, "<<ADC      LED>>");
                Delayms(250);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
            HD44780_Clear();
            HD44780_Puts(0, 0, "1.LCD TEST");
            HD44780_Puts(0, 1, "<<ADC      LED>>");
            
            while(lcd_flag == 0){
                HD44780_Clear();                
                HD44780_Puts(0, 0, "PRESS KEY1 FOR");
                HD44780_Puts(0, 1, "LEFT");
                Delayms(500);
                HD44780_Clear();
                HD44780_Puts(0, 0, "PRESS KEY2 FOR");
                HD44780_Puts(0, 1, "RIGHT");
                Delayms(500);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
        }
        else if (state == STATE_LED) {
            counter = 0;
            led_flag = 0;
            while(led_flag == 0) {
                HD44780_Clear();
                Delayms(250);
                HD44780_Clear();
                HD44780_Puts(0, 0, "2.LED TEST");
                HD44780_Puts(0, 1, "<<LCD     SSEG>>");
                Delayms(250);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
            HD44780_Clear();
            HD44780_Puts(0, 0, "2.LED TEST");
            HD44780_Puts(0, 1, "<<LCD     SSEG>>");
            
            while(led_flag == 0) {
                LAT_LED1 = 1;
                LAT_LED2 = 0;
                Delayms(50);
                LAT_LED1 = 0;
                LAT_LED2 = 1;
                Delayms(50);
            }
            LAT_LED2 = 0;
        }
        else if (state == STATE_SSEG) {
            counter = 0;
            sseg_flag = 0;
            while(sseg_flag == 0) {
                HD44780_Clear();
                Delayms(250);
                HD44780_Clear();
                HD44780_Puts(0, 0, "3.SSEG TEST");
                HD44780_Puts(0, 1, "<<LED   KEYPAD>>");
                Delayms(250);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
            HD44780_Clear();
            HD44780_Puts(0, 0, "3.SSEG TEST");
            HD44780_Puts(0, 1, "<<LED   KEYPAD>>");

            while(sseg_flag == 0) {
                SSEG_Print(1,sseg_counter%10);
                Delayms(10);
                SSEG_Print(2,sseg_counter/10);
                Delayms(10);
                sseg_counter++;
                if(sseg_counter > 99) sseg_counter = 0;
            }
            LATCbits.LATC0 = 0;
            LATCbits.LATC5 = 0;
        }
        else if (state == STATE_KEYPAD) {
            counter = 0;
            keypad_flag = 0;
            while(keypad_flag == 0) {
                HD44780_Clear();
                Delayms(250);
                HD44780_Clear();
                HD44780_Puts(0, 0, "4.KEYPAD TEST");
                HD44780_Puts(0, 1, "<<SSEG     ADC>>");
                Delayms(250);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
            HD44780_Clear();
            HD44780_Puts(0, 0, "4.KEYPAD TEST");
            HD44780_Puts(0, 1, "<<SSEG     ADC>>");

            while(keypad_flag == 0) {
                int_key = KEYPAD_Read();
                char_key = (char)KEYPAD_KeytoASCII(int_key); 
                HD44780_CursorSet(0,0);
                if(int_key != 0xFF)
                    printf("4.KEYPAD TEST: %c", char_key);
                Delayms(50);
            }
        }
        else if (state == STATE_ADC) {            
            counter = 0;
            adc_flag = 0;
            while(adc_flag == 0) {
                HD44780_Clear();
                Delayms(250);
                HD44780_Clear();
                HD44780_Puts(0, 0, "5.ADC TEST");
                HD44780_Puts(0, 1, "<<KEYPAD   LCD>>");
                Delayms(250);
                counter++;
                if(counter > 3) {counter = 0; break;}
            }
            HD44780_Clear();
            HD44780_Puts(0, 0, "5.ADC TEST");
            HD44780_Puts(0, 1, "<<KEYPAD   LCD>>");

            while(adc_flag == 0){
                ConvertADC();
                while( BusyADC() );
                adcin = 1023 - ReadADC();
                dcf_old = dcf;
                dcf = (1-lamda)*dcf + lamda*adcin;
                if(dcf != dcf_old) {
                    HD44780_CursorSet(0,0);
                    printf("5.ADC TEST: %4d", (int)dcf);
                }
            }
        }
        else state = STATE_LCD;        
    }
}

void interrupt low_priority ExternalInterrupt() {
    
    /* Checks Receive Interrupt 0 Flag bit */
    if(INTCONbits.INT0F == 1) {
        INTCONbits.INT0F = 0;  /* Clear Interrupt 0 Flag */        
        if(state == STATE_LCD) {
            lcd_flag = 1;
        }
        else if(state == STATE_LED) {
            led_flag = 1;
        }
        else if(state == STATE_SSEG) {
            sseg_flag = 1;
        }
        else if(state == STATE_KEYPAD) {
            keypad_flag = 1;
        }
        else if(state == STATE_ADC) {
            adc_flag = 1;
        }
        state--;
        if(state < 0) state = 4;
        counter = 0;
    }
    /* Checks Receive Interrupt 1 Flag bit */
    else if(INTCON3bits.INT1F == 1) {
        INTCON3bits.INT1F = 0;  /* Clear Interrupt 1 Flag */
        if(state == STATE_LCD) {
            lcd_flag = 1;
        }
        else if(state == STATE_LED) {
            led_flag = 1;
        }
        else if(state == STATE_SSEG) {
            sseg_flag = 1;
        }
        else if(state == STATE_KEYPAD) {
            keypad_flag = 1;
        }
        else if(state == STATE_ADC) {
            adc_flag = 1;
        }
        state++;
        if(state > 4) state = 0;
        counter = 0;
                
    }
}
