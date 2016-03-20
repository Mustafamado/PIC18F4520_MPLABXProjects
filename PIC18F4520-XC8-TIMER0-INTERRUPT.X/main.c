/**
 * MPLABX IDE project example for blinking LED with Timer0 Interrupt
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
#include <plib/timers.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

/* fcmd = fosc/4 = 32MHz/4 = 8Mhz
 * Tcmd = 1/fcmd = 1/8MHz = 1/(8*10^6) s = 0.125 us
 * TMR0_value = 2^TMR0bit - (DesiredInterruptTime/(Tcmd*Prescaler))
 * Prescaler = 16
 * TMR0bit = 16
 * DesiredInterruptTime = 1ms
 * TMR0_value = 65036
 */

int TMR0_value = 65036; /* Required value for 1 second Timer0 Interrupt */
int millis = 0;

/* LED1 */
#define TRIS_LED1   TRISCbits.RC1
#define LAT_LED1    LATCbits.LATC1
/* LED2 */
#define TRIS_LED2   TRISCbits.RC2
#define LAT_LED2    LATCbits.LATC2

void main(void) {
    
    TRIS_LED1 = 0;
    LAT_LED1 = 0;
    /* Configure Timer0 */
    OpenTimer0(TIMER_INT_ON &  /* Enable TIMER Interrupt */
               T0_16BIT &      /* Timer0 is configured as an 16-bit timer/counter */
               T0_SOURCE_INT & /* Internal instruction cycle clock (CLKO) acts as source of clock */
               T0_PS_1_16);   /* 1:256 Prescale value */

    WriteTimer0(TMR0_value);

    INTCONbits.GIE = 1;
    while (1);
}

void interrupt Interrupt(void) {
    /* If Timer flag is set & Interrupt is enabled */
    if(INTCONbits.TMR0IF==1) {
        INTCONbits.TMR0IF = 0;    /*  Clear the interrupt flag  */
        WriteTimer0(TMR0_value);
        if(++millis == 1000) {            
            LAT_LED1 =~ LAT_LED1;
            millis = 0;
        }
    }
}

/* -----------------------------------------------------------------------------
 *  RCON REGISTER
 * -----------------------------------------------------------------------------
 * IPEN: Interrupt Priority Enable bit, 
 * 1 = Enable priority levels on interrupts, 
 * 0 = Disable priority levels on interrupts (PIC16XXX Compatibility mode)
 */

/* -----------------------------------------------------------------------------
 * INTCON REGISTER
 * -----------------------------------------------------------------------------
 * GIE/GIEH: Global Interrupt Enable bit
 *      When IPEN = 0:
 *          1 = Enables all unmasked interrupts
 *          0 = Disables all interrupts
 *      When IPEN = 1:
 *          1 = Enables all high priority interrupts
 *          0 = Disables all interrupts

 * PEIE/GIEL: Peripheral Interrupt Enable bit
 *      When IPEN = 0:
 *          1 = Enables all unmasked peripheral interrupts
 *          0 = Disables all peripheral interrupts
 *      When IPEN = 1:
 *          1 = Enables all low priority peripheral interrupts
 *          0 = Disables all low priority peripheral interrupts

 * TMR0IF: TMR0 Overflow Interrupt Flag bit
 *      1 = TMR0 register has overflowed (must be cleared in software)
 *      0 = TMR0 register did not overflow

 * TMR0IE: TMR0 Overflow Interrupt Enable bit
 *      1 = Enables the TMR0 overflow interrupt
 *      0 = Disables the TMR0 overflow interrupt
 */

/* ----------------------------------------------------------------------------- 
 * INTCON2 REGISTER
 * -----------------------------------------------------------------------------
 * TMR0IP: TMR0 Overflow Interrupt Priority bit
 *      1 = High priority
 *      0 = Low priority
 */

/* -----------------------------------------------------------------------------
 * T0CON: TIMER0 CONTROL REGISTER
 * -----------------------------------------------------------------------------
 * TMR0ON: Timer0 On/Off Control bit
 *      1 = Enables Timer0
 *      0 = Stops Timer0
 */
