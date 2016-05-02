/**
 * MPLABX IDE project example for HW2 with SSEG TMR1I
 * 
 * @author   Burak Enez
 * @email    burakenez@gmail.com
 * @website  http://burakenez.org
 * @ide      MPLAB X IDE
 * @compiler XC8 v1.34
 * @license  GNU GPL v3
 */
/* Include core modules */
#include <xc.h>
#include <plib/timers.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"
#include "pic18f4520_sseg.h"

/* Timer 0 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR0_value = 2^TMR0bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 16
 * TMR0bit = 16
 * DesiredInterruptTime = 10ms
 * TMR0_value = 60536
 */

/* Timer 1 interrupt value calculation
 * 
 * fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us = 0.125*10^-6 s
 * TMR1_value = 2^TMR1bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 8
 * TMR1bit = 16
 * DesiredInterruptTime = 10ms
 * TMR1_value = 60536
 */

int TMR0_value = 60536; // Required value for 10ms Timer0 Interrupt
int TMR1_value = 55536; // Required value for 10ms Timer1 Interrupt
int counter = 0; // Value that will be shown on ssegs
int flag = 0;
int timer_flag = 0; // To divide time between ssegs
int temp;

void main(void) {
    TRISBbits.RB0 = 1; // KEY1 is input
    TRISBbits.RB1 = 1; // KEY2 is input
    TRISCbits.RC1 = 0; // LED1 is output
    
    LATCbits.LATC1 = 0; // LED1 is off
    
    SSEG_Init();
    
    // Configure Timer0
    OpenTimer0(TIMER_INT_ON     & // Enable TIMER Interrupt
               T0_16BIT         & // Timer0 is configured as an 16-bit timer/counter
               T0_SOURCE_INT    & // Internal instruction cycle clock (CLKO) acts as source of clock
               T0_PS_1_16);       // 1:16 Prescaler value
               
    WriteTimer0(TMR0_value); // Write Timer0 value to Timer0 to count

    OpenTimer1( TIMER_INT_ON    & // Enable TIMER Interrupt
                T1_16BIT_RW     & // Enables register read/write of Timer1 in one 16-bit operation
                T1_SOURCE_INT   & // Internal instruction cycle clock (CLKO) acts as source of clock
                T1_PS_1_8       & // 1:8 prescaler value
                T1_OSC1EN_OFF   & // Timer 1 oscilator enable off
                T1_SYNC_EXT_OFF );// Do not synchronize external clock input
    
    WriteTimer1(TMR1_value); // Write Timer1 value to Timer1 to count
    
    INTCON3bits.INT1E = 1; // Enable Interrupt 1 (RB1 as interrupt)
    INTCON2bits.INTEDG1 = 1; // Interrupt 1 occurs at rising edge
    INTCON3bits.INT1F = 0; // Clear Interrupt 0 flag

    INTCONbits.GIE = 1; // Enables all unmasked interrupts
    INTCONbits.PEIE = 1; // Enables all unmasked peripheral interrupts
    
    while(1) { 
        if(flag == 1) {
            temp = counter;
            for(int i=0; i<temp; i++) {
                LATCbits.LATC1 = 1;
                Delayms(250);
                LATCbits.LATC1 = 0;
                Delayms(250);
                counter--;
            }
            flag = 0;
        }
    }
}

void interrupt ISR(void) {
    
    if(INTCONbits.TMR0IF == 1) { // if Timer0 Interrupt is occurred
        INTCONbits.TMR0IF = 0; // Clear the interrupt flag
        WriteTimer0(TMR0_value); // Update TMR0 value
        if(PORTBbits.RB0 == 0) { // if KEY1 is pressed
            while(PORTBbits.RB0 == 0); // Trap until KEY1 is released            
            counter++; // Increase counter by 1
        }
    }
    
    if(PIR1bits.TMR1IF == 1) { // if Timer1 Interrupt is occurred
        PIR1bits.TMR1IF = 0; // Clear the interrupt flag
        WriteTimer1(TMR1_value); // Update TMR1 value
        if(timer_flag == 0) { // if it is first 10ms
            SSEG_Print(1,counter%10); // Shows ones of counter at first sseg
            timer_flag = 1;
        }
        else { // if it is second 10ms
            SSEG_Print(2,counter/10); // Shows tens of counter at second sseg
            timer_flag = 0;
        }
    }
    
    if(INTCON3bits.INT1F == 1) { // if External Interrupt 1 is occurred (KEY2)
        INTCON3bits.INT1F = 0;  // Clear Interrupt 1 Flag
        flag = 1;
    }
}
