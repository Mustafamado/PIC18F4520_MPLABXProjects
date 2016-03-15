; ------------------------------------------------------------------------------
; MPLABX IDE project example for blinking LED
; 
; @author   Burak Enez
; @email    burakenez@gmail.com
; @website  http://burakenez.org
; @ide      MPLAB X IDE
; @compiler MPASM
; @license  GNU GPL v3
; ------------------------------------------------------------------------------
    
; PIC18F4520 Configuration Bit Settings

; ASM source line config statements

#include "p18F4520.inc"

; CONFIG1H
  CONFIG  OSC = HSPLL           ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOREN = OFF           ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
  CONFIG  BORV = 2              ; Brown Out Reset Voltage bits ()

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = PORTC        ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = OFF          ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

; Variables
	cblock 0x000	;Beginning of Access RAM
	CounterA	;address 0x000		   
	CounterB	;address 0x001
	CounterC	;adresss 0x002
	endc

; Macro definitions
MOVLF	macro	literal,dest
	movlw	literal
	movwf	dest
	endm

; Vectors
	org	0x0000		;Reset vector
	nop
	goto	Main

	org	0x0008		;High priority interrupt vector
	goto	$		;Trap

	org	0x0018		;Low priority interrupt vector
	goto	$		;Trap

; Mainline program
Main		
	rcall	Initial		;Initialize everything

Loop
	;btg	PORTC, RC1	;Toggle pin, to support measuring loop time
	;rcall	Delay		;Make looptime
	bsf	PORTC, RC1
	rcall	Delay1s		;Make looptime
	bcf	PORTC, RC1
	rcall	Delay1s		;Make looptime
	bra	Loop

; Initial subroutine
; This subroutine performs all initializations of variables and registers.
Initial
	MOVLF	B'10001110', ADCON1   ;Enable PORTA & PORTE digital I/0 pins
	MOVLF	B'00000000', TRISA    ;Set I/0 for PORTA
	MOVLF	B'00000000', TRISB    ;Set I/0 for PORTS
	MOVLF	B'00000000', TRISC    ;Set I/0 for PORTC
	MOVLF	B'00000000', TRISD    ;Set I/0 for PORTD
	MOVLF	B'00000000', TRISE    ;Set I/0 for PORTE
	MOVLF	B'00000000', PORTC    ;Turn off all four LEDs driven from PORTA
	return

; Delay1s subroutine 
; Below delay code is generated by using following program:
; http://www.biltronix.com/picloops.html
; FOSC1 = 8MHz (Oscillator frequency on development board)
; OSC = 4 x FOSC1 = 32 MHz
; PIC Time Delay = 1 s with OSC = 32000000 Hz takes 8000000 cycles
; Each instruction is done in 4 osc cycles.	
Delay1s 
	movlw	D'41'
	movwf	CounterC
	movlw	D'150'
	movwf	CounterB
	movlw	D'126'
	movwf	CounterA
Delayloop	
	decfsz	CounterA,1
	goto	Delayloop
	decfsz	CounterB,1
	goto	Delayloop
	decfsz	CounterC,1
	goto	Delayloop
	retlw	0

	
	
	
	end

; Instruciton Sets Used in This Assembly Code
; ------------------------------------------------------------------------------     
; Operand	    Description			    Cycles
; -------------	    --------------		    ---------
; DECFSZ f, d, a    Decrement f, skip if 0	    1 (2 or 3)
; MOVWF f, a	    Move WREG to f		    1
; BCF f, b, a	    Bit clear f			    1
; BSF f, b, a	    Bit set f			    1
; BTG f, d, a	    Bit toggle			    1
; BRA n		    Branch unconditionally	    1 (2)
; CALL n, s	    Call subroutine		    2
; GOTO n	    Goto			    2
; NOP		    No operation		    1
; RCALL n	    Relative call		    2
; RETURN s	    Return from subroutine	    2
; MOVLW k	    Move literal to WREG	    1
; RETLW k	    Return with literal in WREG	    2
; ------------------------------------------------------------------------------

; Instruction Time Calculation 
; ------------------------------------------------------------------------------
; The clock cycle used to drive the CPU core (FOSC) is based on the oscillator 
; frequency (OSC) and on some devices a PLL that can be used to scale the 
; frequency (typically x4 on an 18F). So ...
;
; FOSC = OSC * PLL
;
; For example:
;
; 16F device with 4Mhz internal oscillator and no PLL (treat as x1) means 
; FOSC = 4 Mhz * 1 = 4 Mhz
; 18F device with 8Mhz crystal and 4x PLL enabled means 
; FOSC = 8 Mhz * 4 = 32 Mhz
;
; The 8-bit device core takes 4 clock cycles to decode a single word instruction 	
; (like a NOP)
;
; So the example 4 Mhz 16F device with no PLL can execute 
; 4,000,000 / 4 = 1,000,000 single word instructions per second 
; (e.g. 1 uSec per instruction)
;	
; Example 18F device would do 
; 32,000,000 / 4 = 8,000,000 single word instructions per second 
; (e.g. 0.125 uSec = 125 nSec per instruction).
;
; Some instructions take 8 clock cycles either because they skip over another 
; instruction without executing it (e.g. BTFSS), cause the prefetched 
; instruction to be discarded (e.g. 16F's GOTO, 18F's BRA) or because they 
; contain an memory address that is split over two instruction words 
; (e.g. the 18F's CALL, LFSR, etc).
; ------------------------------------------------------------------------------
