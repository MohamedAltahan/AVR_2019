/*
 * WATCHDOG.c
 *
 *  Created on: Oct 12, 2019
 *      Author: MOHAMED ALTAHAN
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "WDT_INTERFACE.h"

#include "WDT_PRIVATE.h"
/****************************************************************/
/****************** Enable WDT and set the Prescaler ************/
/****************************************************************/

/* this function takes a number from ( 0 - 7) to set the prescaler

0  >>>> 17.1 ms
1  >>>> 34.3 ms
2  >>>> 68.5 ms
3  >>>> 0.14 s
4  >>>> 0.27 s
5  >>>> 0.55 s
6  >>>> 1.1 s
7  >>>> 2.2 s

 */
void WDT_void_Enable(u8 Copy_u8_Prescaler)
{
       /* Enable WDT*/
	   WDTCR  |= (1 << 3) | ( 1 << 4);

	   /*  configure prescaler*/
		 
	   /*prepare the first three bits (zeros)*/
	   WDTCR  &=0b11111000;
	   /*set the first three bits to set the prescaler*/
		WDTCR  |= Copy_u8_Prescaler;
		  
}//end WDT_void_Enable()


/****************************************************************/
/****************** Reset WDT ***********************************/
/****************************************************************/
void WDT_void_Reset(void)
{
    /* to reset WDT and start from the beginning */
	asm("WDR");
	
}//end WDT_void_Reset()

/****************************************************************/
/****************** Disable WDT *********************************/
/****************************************************************/
void WDT_void_Disable(void)
{
	/* Write logical one to WDTOE and WDE( from datasheet) */
	WDTCR = (1<<4) | (1<<3);
	/* Turn off WDT */
	WDTCR = 0x00;
	
}//end WDT_void_Disable()
