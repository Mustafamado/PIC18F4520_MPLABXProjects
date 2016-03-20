/**
 * MPLABX IDE project example for ADC
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
/* Include plib here */
#include <plib/adc.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"
#include "pic18f4520_hd44780.h"

double dcf = 0; /* Average filter */
double dcf_old = 0; /* For better LCD performance */
double lamda = 0.05; /* Average of last 20 ADC read */

void main() {

    int adcin;
    /* Initialize LCD 16 cols x 2 rows */
    HD44780_Init(16, 2);
    /* Configure A/D convertor (ADC_V5) */
    OpenADC(ADC_FOSC_4 &        /* fosc = frequency of oscillator / 4 */
            ADC_RIGHT_JUST &    /* Result in Least Significant bits */
            ADC_0_TAD,          /* A/D Acquisition Time is 12 TAD */
            ADC_CH0 &           /* Channel 0 */
            ADC_REF_VDD_VSS &   /* ADC voltage source VREF+ = VDD and VREF- = VSS */
            ADC_INT_OFF,        /* Interrupts disabled */
            ADC_1ANA);          /* analog: AN0 and remaining channels are digital */
    Delay(50); /* Waits for the acquisition to complete */
    
    HD44780_CursorSet(0,0); /* Move to the beginning of the first line */
    printf("ADC Value:"); /* Print to the first line */    
    
    /* Loop forever */
    while(1) {
        ConvertADC(); /* Start conversion */
        while( BusyADC() ); /* Wait for completion */
        adcin = ReadADC(); /* Read result */
        // CloseADC(); /* Disable A/D converter */
        dcf_old = dcf; /* For better LCD performance */
        dcf = (1-lamda)*dcf + lamda*adcin; /* Filtering the adcin value for better result */
        if(dcf != dcf_old) { /* For better LCD performance */
            HD44780_CursorSet(0,1); /* Move to the beginning of the second line */
            printf("%4d", 1023-(int)dcf); /* Print the AdcValue to the second line */
        }
    }
}
