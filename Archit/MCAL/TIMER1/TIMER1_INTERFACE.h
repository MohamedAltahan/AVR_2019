
#ifndef _TIMER1_INTERFACE_H
#define _TIMER1_INTERFACE_H


#include "STD_TYPES.h"

/*=========================== initialization(mandatory) ========================*/

void TIMER1_void_Init(void);

/*======================== Prescaler / Enable / Disable ========================*/


/*********************************************************************
 * this function takes a value from the following to set prescaler   *
 * and start timer1.												 *
 *********************************************************************
NO_PRESCALER
PRESCALER_8
PRESCALER_64
PRESCALER_256
PRESCALER_1024
COUNTER_FALLING_EDGE     	      // pin T0 as input (By Default)
COUNTER_RISING_EDGE      	      // pin T0 as input (By Default)
*/
void TIMER1_void_Enable(u8 Copy_u8_Prescaler);

//Disable Timer1
void TIMER1_void_Disable(void);


/*=========================== load timer1 registers ============================*/

/* preload a value in TCNT1 from ( 0 - 65,535 ) */
void TIMER1_void_SetTimerRegister_TCNT1(u16 Copy_u16_Value);

/*set a value in OCR1A from ( 0 ­ 65,535 ) in order to
 compare with TCNT1. */
void TIMER1_void_SetCompareValue_OCR1A(u16 Copy_u8_Value);

/*set a value in OCR1B from ( 0 ­ 65,535 ) in order to
 compare with TCNT1. */
void TIMER1_void_SetCompareValue_OCR1B(u16 Copy_u8_Value);

/* set a value in ICR1 from ( 0 ­ 65,535) */
void TIMER1_void_SetCompareValue_ICR1(u16 Copy_u8_Value);


/*====================== Get timer1 TCNT1 register value =======================*/

/* Get the value of ( TCNT1L + TCNT1H) */
u16 TIMER1_u16_GetTimerValue_TCNT1(void);


/*=================================== Interrupts ===============================*/

/*Enables the interrupt of Timer1
 Also active Global interrupt bit */
void TIMER1_void_EnableInterrupt_TCNT1(void);

/*Enables COMPA interrupt and
Also active Global interrupt bit*/
void TIMER1_void_EnableInterrupt_COMPA(void);

/*Enables COMPB interrupt
 Also active Global interrupt bit*/
void TIMER1_void_EnableInterrupt_COMPB(void);


/*Disable the interrupt of Timer1
 Global interrupt bit is still active */
void TIMER1_void_DisableInterrupt_TCNT1(void);

/*Disable COMPA interrupt
  Global interrupt bit still active*/
void TIMER1_void_DisableInterrupt_COMPA(void);

/*Disables COMPB interrupt
  Global interrupt bit is still active */
void TIMER1_void_DisableInterrupt_COMPB(void);


/*============================= Capture unit ===================================*/
/*************************************************************
 * you must Enable Timer1 in order to Enable Capture Unit    *
 *************************************************************/

/**************************************
 * this function :                    *
 * Enables global interrupt -         *
 * Enables Capture Unit interrupt     *
 * Sets ICP pin Direction as input	  *
 * ************************************/
void TIMER1_void_Enable_CaptureUnit_Interrupt (void);

/* Disables Capture Unit interrupt,
 * global interrupt is still active*/
void TIMER1_void_Disable_CaptureUnit_Interrupt (void);

/* Capture on Rising Edge */
void TIMER1_void_CaptureEdge_Rising(void);

/* Capture on Falling Edge */
void TIMER1_void_CaptureEdge_Falling(void);

/* Get the value of ( ICR1L + ICR1H) */
u16 TIMER1_u16_GetCaptureValue_ICR1(void);


/*================================= Callback ===================================*/

/***********************************************************************
 *use this functions in the main and put your function name instead of *
 *pointer to function to pass the address of your function tothe  ISR  *
 *pointer which in the MCAL layer                                      *
 ***********************************************************************/
/* CallBack for Timer1 overflow */
void TIMER1_void_Set_Overflow_CallBack(void (*Copy_ptr) (void) );

/* CallBack for output compare match A overflow */
void TIMER1_void_Set_COMPA_CallBack(void (*Copy_ptr) (void) );

/* CallBack for output compare match B overflow */
void TIMER1_void_Set_COMPB_CallBack(void (*Copy_ptr) (void) );

/* CallBack for input capture unit  */
void TIMER1_void_Set_Capture_CallBack(void (*Copy_ptr) (void) );

#endif
