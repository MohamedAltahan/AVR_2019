/*
 * timer.c
 *
 *  Created on: Oct 3, 2019
 *  edited on : Oct 10,2019
 *      Author: Mohamed Althan
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "TIMER0_INTERFACE.h"
#include "TIMER0_PRIVATE.h"
#include "Timer0_config.h"
#include "REGISTER.h"
#include "avr/interrupt.h"
#include "DIO_INTERFACE.h"


// pinter to function 
void (*TIMER0_OV_CallBack) (void) ;
void (*TIMER0_CTC_CallBack) (void) ;

/********************************************************
*******************initialization for *******************
* TIMER0_MODE - TIMER0_PRESCALER - TIMER0_COMPARE_EVENT *
*********************************************************/

void TIMER0_void_Init(void)
{

/*******************  TIMER0_MODE ***********************/

	#if(TIMER0_MODE == TIMER0_NORMAL)
		CLR_BIT(TCCR0 , 6);
		CLR_BIT(TCCR0 , 3);
	
	#elif(TIMER0_MODE == TIMER0_CTC)
		CLR_BIT(TCCR0 , 6);
		SET_BIT(TCCR0 , 3);
		
	#elif(TIMER0_MODE == TIMER0_FAST_PWM )
		SET_BIT(TCCR0 , 6);
		SET_BIT(TCCR0 , 3);
		
	#elif(TIMER0_MODE == TIMER0_PHASE_PWM )
		SET_BIT(TCCR0 , 6);
		CLR_BIT(TCCR0 , 3);
		
	#endif
	

	
/*******************  TIMER0_COMPARE_EVENT **********************
 *
 * Modes used when using wave generator (output on OC0 pin)     *
 * these modes state what will happen on OC0 pin when the match *
 * happens between (OSR0 and TCNT0).
 *
 * (00)  the  OCO  pin  operates  as  an  I/0  port.
 *
 * (01) Toggle OC0 on compare match, you can use it with normal mode to get
 * (square wave)
 *
 * (10) the waveform generator clears the OCO pin whenever compare
 * match occurs(non-inverted)(the beginning is high) so it is good
 * when we need 100% duty cycle.
 *
 * (11) the waveform generator set the OCO pin whenever compare
 * match occurs( inverted ) (the beginning is low) so it is good
 * when we need 0% duty cycle..
 * **************************************************************/

	#if(TIMER0_COMPARE_EVENT == TIMER0_NO_ACTION)
		CLR_BIT(TCCR0 , 4);
		CLR_BIT(TCCR0 , 5);
		
	
	#elif(TIMER0_COMPARE_EVENT == TIMER0_TOGGLE)
		SET_BIT(TCCR0 , 4);
		CLR_BIT(TCCR0 , 5);
	#elif(TIMER0_COMPARE_EVENT == TIMER0_CLEAR )
		CLR_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
	#elif(TIMER0_COMPARE_EVENT == TIMER0_SET )
		SET_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
	#endif
	/*Disable Interrupts*/
	CLR_BIT(TIMSK , 0);
	CLR_BIT(TIMSK , 1);
	/*CLR FLAGS*/
	SET_BIT(TIFR , 0);	
	SET_BIT(TIFR , 1);
	/*CLR register*/
	TCNT0 = 0 ;
	OCR0 = 0 ;

}//end TIMER0_void_Init()


/****************************************************************/
/*************  Enable Timer1 By setting the prescaler  *********
****************************************************************/
void TIMER0_void_Enable(u8 Copy_u8_Prescaler)
{
    //reset the first three bits of TCCR1B to prepare them to write
	// the new value in them (Bit masking)
	TCCR0 &= (0b11111000);

	//write the first three bits(Bit masking)
	TCCR0 |= Copy_u8_Prescaler;

	// if the prescaler 6 of 7 that mean it works as counter
	//so make pin T1 as input to be the clock source
	if((Copy_u8_Prescaler == 6) || (Copy_u8_Prescaler == 7) )
	   {
	     DIO_void_SetPinDirection(DIO_PORTB,PIN0,IN,PULLUP);
	     return ;
	   }
	     DIO_void_SetPinDirection(DIO_PORTB,PIN3,OUT,NON);

}//end TIMER1_void_Enable()


/****************************************************************/
/*************  Disable Timer1 By setting clear prescaler  bits**
*****************************************************************/
void TIMER0_void_Disable(void)
{
//clear prescaler  bits
	TCCR1B &= 0b11111000;

}//end TIMER1_void_Disable()


/*******************  SetTimerRegister ************************************
* here you can preload a value in TCNT0 from 0 - 255
* in order to preload a value into TCNT0 you must write the value into ISR,
* in order to preload  this value  into TCNT0 each overflow.
***************************************************************************/

void TIMER0_void_SetTimerRegister_TCNT0(u8 Copy_u8_Value)
{
	TCNT0 = Copy_u8_Value ;
}//end TIMER0_void_SetTimerRegister()


/*******************  SetCompareValue **************************
* here you can set a value in OCR0 from ( 0 - 255 ) in order to*
* compare with TCNT0                                           *
****************************************************************/

void TIMER0_void_SetCompareValue_OCR0(u8 Copy_u8_Value)
{
	OCR0 = Copy_u8_Value ;
}//end TIMER0_void_SetCompareValue()


/*******************  Enable overflow interrupt  ***************
*     Timer/Counter0 Overflow Interrupt Enable                 *
****************************************************************/

void TIMER0_void_EnableOverflow_interrupt(void)
{
	/*Enable Global Interrupt*/
	SET_BIT(SREG , 7);
	/*Enable Overflow Interrupt Of Timer Register*/
	SET_BIT(TIMSK , 0);

}//end TIMER0_void_EnableOVInt()


/*******************  Disable overflow interrupt  **************
* Timer/Counter0 Overflow Interrupt Enable                     *
****************************************************************/

void TIMER0_void_DisableOverflow_interrupt(void)
{
	CLR_BIT(TIMSK , 0);
}

/*******************  Enable CTC interrupt       ***************
* Timer/Counter0 Output Compare Match Interrupt Enable         *
****************************************************************/
void TIMER0_void_EnableCTC_interrupt(void)
{
	SET_BIT(SREG , 7);
	SET_BIT(TIMSK , 1);
}//end TIMER0_void_EnableCTC()


/*******************  Disable CTC interrupt      ***************
* Timer/Counter0 Output Compare Match Interrupt Enable         *
****************************************************************/
void TIMER0_void_DisableCTC_interrupt(void)
{
	CLR_BIT(TIMSK , 1);
}//end TIMER0_void_DisableCTC()

/***********************************************************/
/*******************  OverflowCallBack       ***************/
/***********************************************************/

void TIMER0_void_SetOverflowCallBack(void (*Copy_ptr) (void) )
{
// set the address of your function to a pointer(pointer to function)
	TIMER0_OV_CallBack = Copy_ptr ;
}//end TIMER0_void_SetOverflowCallBack()


/************************************************************/
/*******************  OverflowCallBack    *******************/
/************************************************************/
void TIMER0_void_SetCTCCallBack(void (*Copy_ptr) (void) ) 
{
// set the address of your function to a pointer(pointer to function)
	TIMER0_CTC_CallBack = Copy_ptr ;
	
}//end TIMER0_void_SetCTCCallBack()


/*********************************************************************/
/************************ISRs*****************************************/
/*********************************************************************/
/*here is the address of the function that you want to execute in    *
* case of the TIMER0 overflow are fired, so the function in this address will*
* be executed when the interrupt happens                             *
**********************************************************************/
// name of the ISR vector exist in the data sheet page 42

ISR(TIMER0_OVF_vect)
{
	//pointer point to a function
	TIMER0_OV_CallBack();
}


ISR(TIMER0_COMP_vect)
{
	//pointer point to a function
	TIMER0_CTC_CallBack();
}

void delay_ms(u16 ticks)
{
// (*1000)to convert ticks(ms) into (us)
// (/256) to get how many overflows we need
// you have to cast or write ( .0 ) in order to assigning the fraction to integer.
	u16 Loc_u32_Counter = ( ticks * 1000.0 ) / 256;

	TIMER0_void_Enable(PRESCALER_8);//enable timer1 and prescaler by 8

for(u16 counter = 0; counter <= Loc_u32_Counter ;counter++)
   {
        //stuck here until the flag is fired
        while( (GET_BIT(TIFR,0) ) == 0 );
        //clear the flag by setting it
        SET_BIT(TIFR,0);
    }
   TIMER0_void_Disable();//Disable timer1

}//end delay_ms()


