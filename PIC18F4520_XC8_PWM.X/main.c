/**
 * MPLABX IDE project example for PWM
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
/* Include plib here */
#include <plib/timers.h>
#include <plib/pwm.h>
/* Include my libraries here */
#include "pic18f4520_config.h"
#include "pic18f4520_delay.h"

/* 500 Hz PWM (Pulse-Width Modulation)
 * For more information about the fuctions in pwm.h go this website:
 * http://www.jgorasia.com/Files/UBWdemos/Documentation/periph-lib/PWM.htm
 * http://singularengineer.com/programming-pic-18-using-xc8-mplab-x-pwm-using-pwm-h/
 */

/* P.S. : Don't confuse about duty_cycle in this code. It is different. */

/* PWM period = [(PR2) + 1] x 4 x TOSC x (TMR2 prescale value)
 * where PWM period = 1/ Frequency (that will be 1/500 = .002)
 * .002 = [PR2 + 1] x 4 x [1 / 8000000] x 16
 * PR2 + 1 = [.002 x 8000000] / [4 x 16]
 * PR2 + 1 =  250
 * PR2 = 249
 */

char period = 249;
int flag = 1;
int duty_cycle = 0;

void main(void) {
    
    TRISCbits.RC2 = 0; /* PWM1 pin set as output */

    OpenTimer2(T2_PS_1_16); /* Timer2 Prescale 1:16 */

    OpenPWM1(period); /* Open pwm at 500 Hz */
    
    /* Loop forever */
    while(1) {
        if(flag == 1) {
            SetDCPWM1(duty_cycle); /* Change duty cycle */
            duty_cycle++;
            if(duty_cycle == 1024) flag = 0;
        }
        else {
            SetDCPWM1(duty_cycle); /* Change duty cycle */
            duty_cycle--;
            if(duty_cycle == 0) flag = 1;
        }
        Delayms(1);
    }
}
