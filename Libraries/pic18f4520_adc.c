/* adc.c file is created by using all adc functions of PIC18F Legacy Peripheral Libraries v2.0 */
/* 9 March 2016 */

#include <p18cxxx.h>
#include "adc.h"

/* adcbusy.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1) || defined (ADC_V2) || defined (ADC_V3) ||\
    defined (ADC_V4) || defined (ADC_V5) || defined (ADC_V6) ||\
	defined (ADC_V7) ||defined (ADC_V7_1) || defined (ADC_V8) ||\
	defined (ADC_V10) || defined (ADC_V11) || defined (ADC_V12) ||\
	defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V11_1)\
	|| defined (ADC_V13_2) || defined (ADC_V13_3)|| defined (ADC_V14)\
	|| defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
/*************************************************************************************
Function:       char BusyADC(void)

Overview:    This function returns the ADC conversion status

Parameters:  None

Returns:        If the value of GO is ‘1’, then ‘1’ is returned,indicating that the
	           ADC is busy in conversion. If the value of GO is ‘0’, then ‘0’ is
                      returned, indicating that the ADC has completed conversion.

Remarks:     This function returns the complement of the ADCON0 <GO/~DONE> bit
                     status which indicates whether the ADC is busy in conversion.
            
***************************************************************************************/
char BusyADC(void)
{
  return(ADCON0bits.GO);
}

#elif defined (ADC_V9) || defined (ADC_V9_1)
/*************************************************************************************
Function:       char BusyADC(void)

Overview:    This function returns the ADC conversion status.  

Parameters:  None

Returns:        If the value of GO is ‘1’, then ‘1’ is returned,indicating that the
	           ADC is busy in conversion. If the value of GO is ‘0’, then ‘0’ is 
                      returned, indicating that the ADC has completed conversion. 

Remarks:     This function returns the complement of the ADCON0 <GO/~DONE> bit
                     status which indicates whether the ADC is busy in conversion.
            
***************************************************************************************/
char BusyADC(void)
{
  WDTCONbits.DEVCFG = 0;  
  return(ADCON0bits.GO);
}

#elif	defined (ADC_V15) || defined (ADC_V15_1)	
/*************************************************************************************
Function:    char BusyADC10(void)

Overview:    This function returns the ADC conversion status.  

Parameters:  None

Returns:     If the value of DONE is ‘0’, then ‘1’ is returned,indicating that the
             ADC is busy in conversion.If the value of DONE is ‘1’, then ‘0’ is 
             returned, indicating that the ADC has completed conversion. 

Remarks:     This function returns the complement of the ADCON1L <DONE> bit
             status which indicates whether the ADC is busy in conversion.
            
***************************************************************************************/  
char BusyADC(void)
{
  return(ADCON1Lbits.DONE);
}

#endif

/* adcclose.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1) || defined (ADC_V2) || defined (ADC_V3) ||\
    defined (ADC_V4) || defined (ADC_V5) || defined (ADC_V8) ||\
	defined (ADC_V6) || defined (ADC_V7) || defined (ADC_V7_1)||\
	defined (ADC_V10)|| defined (ADC_V11) || defined (ADC_V12) ||\
	defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V11_1)\
	|| defined (ADC_V13_2) || defined (ADC_V13_3)|| defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
/*************************************************************************************
Function :       void CloseADC(void)

Overview :    This function turns off the ADC module and disables the ADC interrupts

Parameters :  None

Returns :        None

Remarks :     This function first disables the ADC interrupt and then turns off the ADC
		module.The Interrupt Flag bit (ADIF) is also cleared.
            
***************************************************************************************/
void CloseADC(void)
{
  ADCON0bits.ADON = 0;
  PIE1bits.ADIE = 0;
}

#elif defined (ADC_V9) || defined (ADC_V9_1)
/*************************************************************************************
Function :       void CloseADC(void)

Overview :    This function turns of the ADC module and disables the ADC interrupts

Parameters :  None

Returns :        None

Remarks :     This function first disables the ADC interrupt and then turns off the ADC
		module.The Interrupt Flag bit (ADIF) is also cleared.
            
***************************************************************************************/
void CloseADC(void)
{
  WDTCONbits.DEVCFG = 0;  
  ADCON0bits.ADON = 0;
  PIE1bits.ADIE = 0;
}

#elif defined (ADC_V15) || defined (ADC_V15_1)
/*************************************************************************************
Function :       void CloseADC(void)

Overview :    This function turns of the ADC module and disables the ADC interrupts

Parameters :  None

Returns :        None

Remarks :     This function first disables the ADC interrupt and then turns off the ADC
		module.The Interrupt Flag bit (ADIF) is also cleared.
            
***************************************************************************************/
void CloseADC(void)
{
  ADCON1Hbits.ADON = 0;
  PIE1bits.ADIE = 0;
}
#endif

/* adcconv.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1) || defined (ADC_V2) || defined (ADC_V3) ||\
 defined (ADC_V5) || defined (ADC_V8) ||defined (ADC_V4) || \
 defined (ADC_V6) || defined (ADC_V7) ||defined (ADC_V7_1)||\
 defined (ADC_V10) || defined (ADC_V11) || defined (ADC_V12) ||\
 defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V11_1)\
 || defined (ADC_V13_2) || defined (ADC_V13_3)|| defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
/************************************************************************************
Function       : void ConvertADC(void)
 
Overview     : This function starts the A/D conversion.
 
Parameters   : None

Returns         : None

Remarks        : This function sets the ADCON0<GO> bit and thus
		    starts conversion.
**************************************************************************************/ 
void ConvertADC(void)
{
  ADCON0bits.GO = 1;
}

#elif defined (ADC_V9) || defined (ADC_V9_1)
/************************************************************************************
Function       : void ConvertADC(void)
 
Overview     : This function starts the A/D conversion.
 
Parameters   : None

Returns         : None

Remarks        : This function sets the ADCON0<GO> bit and thus
		    starts conversion.
**************************************************************************************/ 
void ConvertADC(void)
{
  WDTCONbits.DEVCFG = 0;  
  ADCON0bits.GO = 1;
}

#elif defined (ADC_V15) || defined (ADC_V15_1)
/************************************************************************************
Function       : void ConvertADC(void)
 
Overview     : This function starts the A/D conversion.
 
Parameters   : None

Returns         : None

Remarks        : This function clears the ADCON1L<SAMP> bit and thus stops 
                 sampling and starts conversion.This happens only when 
                 trigger source for the A/D conversion is selected as Manual,
                 by clearing the ADCON1L <SSRC> bits.
**************************************************************************************/ 
void ConvertADC(void)
{
  ADCON1Lbits.SAMP = 0; /* clear SAMP to start conversion*/
}
#endif

/* adcopen.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1)
void OpenADC( unsigned char config, 
              unsigned char config2)
{
  ADCON0 = 0;

  ADCON1 = config;
  ADCON0 = ((config<<2) & 0xC0)|(config2 & 0b00111000);
  if( config2 & 0b10000000 )
  {
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
  }
  ADCON0bits.ADON = 1;
}

#elif defined (ADC_V2)
void OpenADC( unsigned char config, 
              unsigned char config2)
{
  ADCON0 = 0;
  ADCON1 = 0;
  ADCON2 = 0;
  
  ADCON0 = (config2 >> 1) & 0b00111100;
  ADCON1 = ((config2 << 4) & 0b00110000) |
           (config & 0b00001111);
  ADCON2 = (config & 0b10000000) |
           ((config >> 4) & 0b00000111);

  if( config2 & 0b10000000 )
  {
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.PEIE = 1;
  }
  ADCON0bits.ADON = 1;
}

#elif defined (ADC_V3)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned char portconfig)
{
    ADCON0 = 0;
    ADCON2 = 0;

    ADCON0 = ((config2 >> 1) & 0b00111100) |
	         ((config2 << 6) & 0b11000000);
	ADCON1 = portconfig;
    ADCON2 = ((config & 0b10000000)|((config >> 4) & 0b00000111)) |
	         ((config << 2) & 0b00111000);

    if( config2 & 0b10000000 )
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V4) || defined (ADC_V5) || defined (ADC_V6)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned char portconfig)
{
    ADCON0 = 0;
    ADCON2 = 0;

    ADCON0 = (config2 >> 1) & 0b00111100;	// GET CHANNELS 
    ADCON1 = (portconfig & 0b00001111) |                   // GET CONFIG
	         ((config2 << 4) & 0b00110000); //GET  Vref
    ADCON2 = (config & 0b10000000)	|	// RESULT
             ((config >> 4) & 0b00000111) |	// CONV CLK
             ((config << 2) & 0b00111000);	// ACQ TIME

    if( config2 & 0b10000000 )			// ADC INT.
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V8)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned int portconfig)
{
    ADCON0 = 0;
    ADCON1 = 0;
    ADCON2 = 0;

    ADCON0 = (config2 >> 1) & 0b00111100;
    ADCON1 |= (config2 << 4) & 0b00110000;
    ADCON2 = config & 0b10000000 |
             ((config >> 4) & 0b00000111) |
             ((config << 2) & 0b00111000);

    ANSEL = portconfig;
    ANSELH = (portconfig >> 8);
	if( config2 & 0b10000000 )
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V7)
void OpenADC( unsigned char config1, 
              unsigned char config2, 
              unsigned char config3)
{	// Reset A/D Registers to POR state    
	ADCON0 = 0;
    ADCON1 = 0;
	ADCON3 = 0;	
	ANSEL0 = 0;
	ANSEL1 = 0;
	ADCHS  = 0;
	
	ADCON0 = (config1<<2) & 0b00111100;	//assign Conv type, conv mode and conv seq.
	ADCON1 = (config2 & 0b11000000) | ((config2 >>1) & 0b00010000);
	ADCON2 = config3;
	ADCON3 = (config2 & 0b00011111) | (config1 & 0b11000000);
    if(config1 & 0b00100000)	
	{
		PIR1bits.ADIF = 0;
      	PIE1bits.ADIE = 1;
      	INTCONbits.PEIE = 1;
	}
	ADCON0bits.ADON = 1;         // Enable the A/D module
}

#elif defined (ADC_V7_1)
void OpenADC( unsigned char config1, 
              unsigned char config2, 
              unsigned char config3)
{	// Reset A/D Registers to POR state    
	ADCON0 = 0;
    ADCON1 = 0;
	ADCON3 = 0;	
	ANSEL0 = 0;
	ADCHS  = 0;
	
	ADCON0 = (config1<<2) & 0b00111100;	//assign Conv type, conv mode and conv seq.
	ADCON1 = (config2 & 0b11000000) | ((config2 >>1) & 0b00010000);
	ADCON2 = config3;
	ADCON3 = (config2 & 0b00011111) | (config1 & 0b11000000);
    if(config1 & 0b00100000)	
	{
		PIR1bits.ADIF = 0;
      	PIE1bits.ADIE = 1;
      	INTCONbits.PEIE = 1;
	}
	ADCON0bits.ADON = 1;         // Enable the A/D module
}

#elif defined (ADC_V9) || defined (ADC_V9_1)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned int portconfig)
{
    WDTCONbits.ADSHR = 0;
    ADCON0 = 0;
    ADCON1 = 0;

    ADCON0 = ((config2 >> 1) & 0b00111100) | //channel
             ((config2 << 6) & 0b11000000);	//VREF
    ADCON1 = (config & 0b10000000) | //Result Format
             ((config >> 4) & 0b00000111) | //Conversion clock select
             ((config << 2) & 0b00111000); //acquisition time

    WDTCONbits.ADSHR= 1;
    ANCON0 = portconfig;
    ANCON1 = (portconfig >> 8);
    WDTCONbits.ADSHR= 0;	

	if( config2 & 0b10000000 )
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V10)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned char config3,
              unsigned int portconfig)
{
    ADCON0 = 0;
    ADCON1 = 0;
    ADCON2 = 0;

    ADCON0 = (config2 >> 1) & 0b00111100;  			//channel selection 
    ADCON1 = (config3 & 0b00001100) | //Positive Voltage Reference Configuration bits
             (config3 & 0b00000011);  //Negative Voltage Reference Configuration bits    
    ADCON2 = (config & 0b10000000) |
             ((config >> 4) & 0b00000111) |		//A/D Conversion Clock Select bits
             ((config << 2) & 0b00111000);		//A/D Acquisition Time Select bits 

    ANSEL = portconfig;							//Didn't Change
    ANSELH = (portconfig >> 8);					//Didn't Change
    
	if( config2 & 0b10000000 )					//interrupt enable check
    {
      PIR1bits.ADIF = 0;						//Clear the ADC Interrupt bit
      PIE1bits.ADIE = 1;						//Enable the ADC Interrupt
      INTCONbits.PEIE = 1;						//Peripheral Interrupt Enable
    }
    ADCON0bits.ADON = 1;						//A/D Conversion Status bit--A/D converter module is operating
}

#elif defined (ADC_V11)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned int  config3)
{    
    ADCON0 = 0;
    ADCON1 = 0;

    ADCON0 = ((config2 >> 1) & 0b00111100) | //channel selection
             ((config2 << 6) & 0b11000000);	//VREF			 
    ADCON1 = (config & 0b10000000) | //Result Format 
             ((config >> 4) & 0b00000111) | //Conversion clock select
             ((config << 2) & 0b00111000); //acquisition time
			 
    ANCON0 = config3; // port configuration
    ANCON1 = config3 >> 8;  // VBG Selection and port configuration

	if( config2 & 0b10000000 )
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V11_1)
void OpenADC( unsigned char config,
              unsigned char config2,
			  unsigned char config3,
              unsigned int  portconfig)
{    
    ADCON0 = 0;
    ADCON1 = 0;

    ADCON0 = ((config2 >> 1) & 0b00111100) | //channel selection
             ((config2 << 6) & 0b11000000);	//VREF			 
    ADCON1 = (config & 0b10000000) | //Result Format 
             ((config >> 4) & 0b00000111) | //Conversion clock select
             ((config << 2) & 0b00111000); //acquisition time
			 
    ANCON0 = portconfig; // port configuration
    ANCON1 = portconfig >> 8;  // VBG Selection and port configuration
	
	ADCTRIG = (config3&0xC0)>>6;

	if( config2 & 0b10000000 )
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V12)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned char config3)
{
    ADCON0 = 0;
    ADCON2 = 0;

    ADCON0 = (config2 >> 1) & 0b00111100;	// GET CHANNELS 
    ADCON1 = (config3  & 0b10001111)|   
	         ((config2 << 4) & 0b00110000); //GET  Vref
    ADCON2 = (config & 0b10000000)	|	// RESULT
             ((config >> 4) & 0b00000111) |	// CONV CLK
             ((config << 2) & 0b00111000);	// ACQ TIME

    if( config2 & 0b10000000 )			// ADC INT.
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

#elif defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V13_2)\
	|| defined (ADC_V13_3) || defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
void OpenADC( unsigned char config,
              unsigned char config2,
              unsigned char config3)
{
    ADCON0 = 0;
	ADCON1 = 0;
    ADCON2 = 0;

    ADCON0 = (config2) & 0b01111100;	// GET CHANNELS 
	
    ADCON1 = config3; // Vref+/- & Trigger & Negetive channel select
			 
    ADCON2 = (config & 0b10000000)	|	// RESULT
             ((config >> 4) & 0b00000111) |	// CONV CLK
             ((config << 2) & 0b00111000);	// ACQ TIME
	
    if( config2 & 0b10000000 )			// ADC INT.
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}


#elif defined (ADC_V15) || defined (ADC_V15_1)
void OpenADC( unsigned char config,
			  unsigned char config1,
              unsigned char config2,
              unsigned char config3,
			  unsigned char config4,
			  unsigned char config5,
              unsigned char config6,
              unsigned char config7
			  )
{
    ADCON1L = 0;
	ADCON1H = 0;
    ADCON2L = 0;
	ADCON2H = 0;
	ADCON3L = 0;
    ADCON3H = 0;
	ADCON5L = 0;
    ADCON5H = 0;

    ADCON1H = config;	// Mode and O/P format
	ADCON1L = (config1) | 0b00000010; //Trigger  & Sample enable bit 
			 
    ADCON2H = config2; // Vref+/- , OFFCAL mode & BUFREGEN
	ADCON2L = config3; // Interrupt sample ,Alt i/p mode
	
	ADCON3L = (config4) | 0b11111111;	//  CONV CLK
	ADCON3H = (config5) | 0b00001111;  // Auto Sample Time select bits
	
	ADCON5L = config6; // Write & Compare mode bits
    ADCON5H = config7; // Auto-Scan bits
	
    if( config & 0b10000000 )			// ADC INT. (ADON is the last bit and hence that is verified to set the interrupts)
    {
      PIR1bits.ADIF = 0;
      PIE1bits.ADIE = 1;
      INTCONbits.PEIE = 1;
    }
    ADCON1Hbits.ADON = 1;
}
#endif

/* adcread.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1) || defined (ADC_V2) || defined (ADC_V3) ||\
    defined (ADC_V4) || defined (ADC_V5) || defined (ADC_V6) ||\
    defined (ADC_V7) || defined (ADC_V7_1) || defined (ADC_V8) ||\
    defined (ADC_V9) || defined (ADC_V9_1) || defined (ADC_V10) || defined (ADC_V11) ||\
	defined (ADC_V12) || defined (ADC_V13) || defined (ADC_V13_1)\
	|| defined (ADC_V11_1) || defined (ADC_V13_2) || defined (ADC_V13_3)\
	|| defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
/*************************************************************************************
Function:       int ReadADC(void)

Overview:    This function reads the ADC Buffer register which contains
                      the conversion value.

Parameters:  None

Returns:        Returns the ADC Buffer value

Remarks:     None
            
***************************************************************************************/	
int ReadADC(void)
{
  return (((unsigned int)ADRESH)<<8)|(ADRESL);
}

#elif	defined (ADC_V15) || defined (ADC_V15_1)
/************************************************************************
Function           : unsigned int ReadADC(unsigned char bufIndex) 

Overview           : This function reads the ADC Buffer register which contains 
                     the conversion value. 

Parameters         : bufIndex - This is the ADC buffer number which is to be read. 

Returns            : Returns the ADC Buffer value

Remarks            : This function returns the contents of the ADC Buffer register.
                     User should provide bufIndex value between ‘0’ to ‘15’ to 
                     ensure correct read of the ADCBUF0 to ADCBUFF.
 ************************************************************************/

unsigned int ReadADC(unsigned char bufIndex)
{
     return(*(&ADCBUF0+bufIndex));
}
#endif

/* adcsetchconv.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1)
void SelChanConvADC(unsigned char channel)
{
  ADCON0 = (ADCON0 & 0b11000011)|
           (channel & 0b00111000);
  ADCON0bits.GO = 1;
}

#elif defined (ADC_V2) || defined (ADC_V3) || defined (ADC_V4) ||\
      defined (ADC_V5) || defined (ADC_V6) || defined (ADC_V8) ||\
	  defined (ADC_V10)|| defined (ADC_V11) || defined (ADC_V12) || defined (ADC_V11_1)
void SelChanConvADC(unsigned char channel)
{
  ADCON0 = (ADCON0 & 0b11000011)|
           ((channel >> 1) & 0b00111100);
  ADCON0bits.GO = 1;
}

#elif defined (ADC_V9) || defined (ADC_V9_1)
void SelChanConvADC(unsigned char channel)
{
    WDTCONbits.DEVCFG = 0;   
    ADCON0 = (ADCON0 & 0b11000011)|
	         ((channel >> 1) & 0b00111100);   
    ADCON0bits.GO = 1;
}

#elif defined (ADC_V7) 
void SelChanConvADC( unsigned char channel)
{	
   if(channel!=8)
      ANSEL0 = 0b00000001 << channel;
   else
      ANSEL1 = 0b00000001;
	  
   switch (channel)
    {
        case 0: 
		        ADCHS |=  0b00000011;
	            ADCHS &=  0b11111100;
			    break;			   
	    case 4: 
		        ADCHS |=  0b00000011;
				ADCHS &=  0b11111101;		
	            break;
	    case 8:
                ADCHS |=  0b00000011;
				ADCHS &=  0b11111110;		
	            break;
        case 1: 
		        ADCHS |=  0b00110000;
				ADCHS &=  0b11001111;
	            break;
		case 5: 
		        ADCHS |=  0b00110000;
				ADCHS &=  0b11011111;
	            break;
		case 2:
                ADCHS |=  0b00001100;
				ADCHS &=  0b11110011; 		
	            break;
		case 6: 
		        ADCHS |=  0b00001100;
				ADCHS &=  0b11110111;
	           break;
		case 3: 
		        ADCHS |=  0b11000000;
				ADCHS &=  0b00111111;
	            break;
		case 7: 
		        ADCHS |=  0b11000000;
			    ADCHS &=  0b01111111;
	            break;	
    }
  ADCON0bits.GO = 1;	
}

#elif defined (ADC_V7_1)
void SelChanConvADC( unsigned char channel)
{	
    ANSEL0 = 0b00000001 << channel;
    
   switch (channel)
    {
        case 0: 
		        ADCHS |=  0b00000011;
	            ADCHS &=  0b11111100;
			    break;			   
	    case 4: 
		        ADCHS |=  0b00000011;
				ADCHS &=  0b11111101;		
	            break;
	    case 1: 
		        ADCHS |=  0b00110000;
				ADCHS &=  0b11001111;
	            break;
		case 2:
                ADCHS |=  0b00001100;
				ADCHS &=  0b11110011; 		
	            break;
		case 3: 
		        ADCHS |=  0b11000000;
				ADCHS &=  0b00111111;
	            break;		
    }
  ADCON0bits.GO = 1;	
}

#elif defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V13_2)\
	|| defined (ADC_V13_3) || defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
void SelChanConvADC(unsigned char channel)
{
  ADCON0 = (ADCON0 & 0b10000011)|
           ((channel) & 0b01111100);
  ADCON0bits.GO = 1;
}

#elif defined (ADC_V15) || defined (ADC_V15_1) 
void SelChanConvADC(unsigned char channelA , unsigned char channelB )
{
  ADCHS0L = (ADCHS0L & 0b00000000)|
           ((channelA) & 0b11111111);
  ADCHS0H = (ADCHS0H & 0b00000000)|
           ((channelB) & 0b11111111); 
  ADCON1Lbits.SAMP = 0;		   
}
#endif

/* adcsetch.c (Combined with all adc functions in adc.c by Burak Enez) */

#if defined (ADC_V1)
/*Description:
  void SetChanADC(unsigned char
  channel)
  
  This function Select the channel
  used as input to the A/D converter.
  Input:
  channel -  This contains the
             \parameters to be
             configured in the ADCON0
             register as defined below
  Return:
  None
  Remarks:
  Selects the pin that will be used as
  \input to the A/D converter.        */
void SetChanADC(unsigned char channel)
{
  ADCON0 = (channel & 0b00111000) |
           (ADCON0 & 0b11000111);
}

#elif defined (ADC_V2) || defined (ADC_V3) || defined (ADC_V4) ||\
      defined (ADC_V5) || defined (ADC_V6) || defined (ADC_V8)|| \
	  defined (ADC_V10)|| defined (ADC_V11) || defined (ADC_V12) || defined (ADC_V11_1)
void SetChanADC(unsigned char channel)
{

  ADCON0 = ((channel >> 1) & 0b00111100) |
           (ADCON0 & 0b11000011);

}
#elif defined (ADC_V9) || defined (ADC_V9_1)
void SetChanADC(unsigned char channel)
{

  WDTCONbits.DEVCFG = 0;  
  ADCON0 = ((channel >> 1) & 0b00111100) |
 	       (ADCON0 & 0b11000011);

}

#elif defined (ADC_V13) || defined (ADC_V13_1) || defined (ADC_V13_2)\
	|| defined (ADC_V13_3) || defined (ADC_V14) || defined (ADC_V14_1) || defined (ADC_V14_2) || defined (ADC_V14_3)
void SetChanADC(unsigned char channel)
{
  ADCON0 = (ADCON0 & 0b10000011)|
           ((channel) & 0b01111100);
}

#elif defined (ADC_V15) || defined (ADC_V15_1) 
void SetChanADC(unsigned char channelA , unsigned char channelB )
{
  ADCHS0L = (ADCHS0L & 0b00000000)|
           ((channelA) & 0b11111111);
  ADCHS0H = (ADCHS0H & 0b00000000)|
           ((channelB) & 0b11111111); 
} 		   
#endif
