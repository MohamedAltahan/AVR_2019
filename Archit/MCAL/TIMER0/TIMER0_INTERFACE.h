/*
 * timer.c
 *
 *  Created on: Oct 3, 2019
 *  edited on : Oct 10,2019
 *      Author: Mohamed Althan
 */
#ifndef _TIMER0_INTERFACE_H
#define _TIMER0_INTERFACE_H
#include "STD_TYPES.h"

/* **************************************************************************
 * Good to know :												            *
 * in order to preload a value into TCNT0 you must write the value into ISR,*
 * to preload  this value into TCNT0 each overflow.							*
 * OR :																		*
 * you can preload in you main while loop (not good way)					*
 ****************************************************************************/

/*================================ initialization ===============================*/
void TIMER0_void_Init(void);

/*==================== prescaler / Enable / Disable =============================*/

/************************************************************************
 * this function takes a value from the following  to set the prescaler *
 *  and starts timer0.                                                  *
 ************************************************************************
NO_PRESCALER
PRESCALER_8
PRESCALER_64
PRESCALER_256
PRESCALER_1024
COUNTER_FALLING_EDGE     	      // pin T0 as input (by default)
COUNTER_RISING_EDGE     	      // pin T0 as input (by default)
*/
void TIMER0_void_Enable(u8 Copy_u8_Prescaler);

/* to Disable timer0 */
void TIMER0_void_Disable(void);


/*============================ Load Timer0 Registers ============================*/

/*here you can preload the Timer0 with a value in TCNT0 from 0 - 255 */
void TIMER0_void_SetTimerRegister_TCNT0(u8 Copy_u8_Value);

/*set a value in OCR0 from ( 0 - 255 ) in order to
 compare with TCNT0. and output appear on OC0 */
void TIMER0_void_SetCompareValue_OCR0(u8 Copy_u8_Value);


/*====================================== interrupts =============================*/


/*Enables the interrupt when the flag is fired
Also active Global interrupt bit */
void TIMER0_void_EnableOverflow_interrupt(void);

/*Enables CTC interrupt
Also active Global interrupt bit*/
void TIMER0_void_EnableCTC_interrupt(void);

/* Disable the interrupt of timer
 Global interrupt bit still active */
void TIMER0_void_DisableOverflow_interrupt(void);

/*Disable the interrupt of CTC,
  Global interrupt bit still active*/
void TIMER0_void_DisableCTC_interrupt(void);

/*================== delay function using timer0 ================================*/

/* using timer to generate delay */
void delay_ms(u16 ticks);

/*==================================== callback =================================*/

/*use this functions in the main and put your function name instead of
pointer to function to pass the address of your function to ISR which
in the MCAL layer*/

/* callback for timer0 overflow */
void TIMER0_void_SetOverflowCallBack(void (*Copy_ptr) (void) ) ;

/* callback for compare match ( CTC mode) overflow */
void TIMER0_void_SetCTCCallBack(void (*Copy_ptr) (void) ) ;

/*===================================== flags ==================================*/

/* timer0 overflow flag (TOV0) :
           in       ( Register : TIFR ,  BIT : 0 ) */
/* output compare(CTC mode) overflow flag( OCF0) :
           in       ( Register : TIFR ,  BIT :  1 ) */

#endif
