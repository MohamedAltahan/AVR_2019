/********************************************/
/* Author   : MOHAMED ALTAHAN               */
/* Date     : 25 SEP 2019                   */
/* Version  : V1                            */
/********************************************/

#include "BIT_MATHS.h"
#include "STD_TYPES.h"
#include "EX_INT_PRIVATE.h"
#include "DIO_INTERFACE.h"

#include "EX_INT_INTERFACE.h"
#include "EX_INT_CONFIG.h"
#include "avr/interrupt.h"

/* Declaration of three (pointers to function) to contain the addresses
of the functions which in the main*/

void(*INT0_CallBack)(void);
void(*INT1_CallBack)(void);
void(*INT2_CallBack)(void);

/**********************************************************************
*				Initialization of External Interrupts                 *
*				Clears all the flags .                           	  *
***********************************************************************/
void INT_void_Init(void)
 {

	// Clear Flag Bit at the beginning
	CLR_BIT(GIFR, 5);
	CLR_BIT(GIFR, 6);
	CLR_BIT(GIFR, 7);

	SET_BIT(SREG , 7);  //Disable global interrupt

 }//end EX_TI_vidInitialize()


/**********************************************************************
*				set the trigger level for INT0       				  *
*               changes the first two bits of MCUCR 				  *
*         LOW_LEVEL - ON_CHANGE - FALLING_EDGE - RISING_EDGE          *
***********************************************************************/
void INT0_void_TriggerLevel(u8 Cpy_u8_TrigLevel)
 {
	//prepare the first two bits (make them zeros)
 		MCUCR &= 0b11111100;
 	//set the value of the first two bits
		MCUCR |= Cpy_u8_TrigLevel;
 }


/**********************************************************************
*				set the trigger level for INT1       				  *
*               changes bit2 and bit3 of MCUCR                        *
*     LOW_LEVEL - ON_CHANGE - FALLING_EDGE - RISING_EDGE  		  	  *
***********************************************************************/
void INT1_void_TriggerLevel(u8 Cpy_u8_TrigLevel)
 {
	//prepare bit2 and bit3 (make them zeros)
 		MCUCR &= 0b11110011;
 	//set the value of bit2 and bit3
		MCUCR |= Cpy_u8_TrigLevel;
 }


/**********************************************************************
*				set the trigger level for INT2       				  *
*               changes bit2 and bit3 of MCUCR                        *
*               FALLING_EDGE - RISING_EDGE only           	      	  *
***********************************************************************/
void INT2_void_TriggerLevel(u8 Cpy_u8_TrigLevel)
 {
	  //prepare bit6  (make it zero)
	   MCUCSR &= 0b10111111;
	  //set the value of bit6
	   MCUCSR |= Cpy_u8_TrigLevel;
 }



/*************************EXT_INT0 Enable**************************/
void INT0_void_Enable(void)
 {
	SET_BIT(SREG , 7);  //enable global interrupt
	SET_BIT(GICR, 6);	//enable EXINT0
	// Set PD2 (INT0) to input direction
	DIO_void_SetPinDirection(DIO_PORTD,PIN2,IN, INT0_PULLING );


 }//END EX_INT0_void_Enable()

/************************EXT_INT1 Enable**************************/

void INT1_void_Enable(void)
 {
	SET_BIT(SREG , 7);  //enable global interrupt
	SET_BIT(GICR, 7);	//enable EXINT0
	// Set PD3 (INT1) to input direction
	DIO_void_SetPinDirection(DIO_PORTD,PIN3,IN,INT1_PULLING);

 }//END EX_INT1_void_Enable()


/**************************EXT_INT2 Enable************************/

void INT2_void_Enable(void)
 {
	SET_BIT(SREG , 7);  //enable global interrupt
	SET_BIT(GICR, 5);	//enable EXINT0
	// Set PD3 (INT2) to input direction
	DIO_void_SetPinDirection(DIO_PORTB,PIN2,IN,INT2_PULLING);

 }//END EX_INT2_void_Enable()

/*************************EXT_INT0 Disable**************************/
void INT0_void_Disable(void)
 {

	CLR_BIT(GICR, 6);	//Disable EXINT0

 }//END EX_INT0_void_Disable()

/************************EXT_INT1 Disable**************************/

void INT1_void_Disable(void)
 {

	CLR_BIT(GICR, 7);	//Disable EXINT0

 }//END EX_INT1_void_Disable()


/************************** EXT_INT2 Disable ************************/

void INT2_void_Disable(void)
 {

	CLR_BIT(GICR, 5);	//Disable EXINT0

 }//END EX_INT2_void_Disable()



/*******************************************************************
* functions that receive the address of your functions which exist *
*  in the main                                                     *
********************************************************************/
void INT0_vidSetCallBack( void(*Copy_ptr)(void) )
 {

//this sets the address of your functions to a pointer
	INT0_CallBack = Copy_ptr;
 }

void INT1_vidSetCallBack( void(*Copy_ptr)(void) )
 {
	INT1_CallBack = Copy_ptr;
 }

void INT2_vidSetCallBack( void(*Copy_ptr)(void) )
 {
	INT2_CallBack = Copy_ptr;
 }


/*********************************************************************/
/************************ISRs*****************************************/
/*********************************************************************/
/*here is the address of the function that you want to execute in    *
* case of the INT0..2 are fired, so the function in this address will*
* be executed when the interrupt happens                             *
**********************************************************************/

ISR(INT0_vect)
{
	INT0_CallBack();
}


ISR(INT1_vect)
{
	INT1_CallBack();
}


ISR(INT2_vect)
{
	INT2_CallBack();
}


