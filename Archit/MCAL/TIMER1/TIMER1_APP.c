

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "TIMER1_INTERFACE.h"
#include "TIMER1_PRIVATE.h"
#include "TIMER1_CONFIG.h"
#include "REGISTER.h"
#include "avr/interrupt.h"
#include "DIO_INTERFACE.h"


// pinter to function 
void (*TIMER1_TOV1_CallBack)  (void) ;
void (*TIMER1_COMPA_CallBack) (void) ;
void (*TIMER1_COMPB_CallBack) (void) ;
void (*TIMER1_Capture_CallBack)  (void);

/********************************************************
*******************initialization for *******************
* TIMER1_MODE -  TIMER1_COMPARE_EVENT *
*********************************************************/

void TIMER1_void_Init(void)
{

/*******************  TIMER1_MODE ***********************/
	/*LOOK AT DATASHEET TO KNOW WHEN IS THE FLAG FIRED
	 * OF EACH CASE PAGE 107 */

	#if(TIMER1_MODE == TIMER1_NORMAL)
CLR_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);
	
#elif(TIMER1_MODE == TIMER1_CTC_OCR1A)
CLR_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

#elif(TIMER1_MODE == TIMER1_CTC_ICR1)
CLR_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

	#elif(TIMER1_MODE == TIMER1_PHASE_PWM_8BIT )
SET_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

	#elif(TIMER1_MODE == TIMER1_PHASE_PWM_9BIT )
CLR_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_PHASE_PWM_10BIT )
SET_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);
		
    #elif(TIMER1_MODE == TIMER1_PHASE_PWM_ICR1 )
CLR_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_PHASE_PWM_OCR1A )
SET_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_FAST_PWM_8BIT )
SET_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_FAST_PWM_9BIT )
CLR_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_FAST_PWM_10BIT )
SET_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
CLR_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_FAST_PWM_ICR1 )
CLR_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);

SET_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_FAST_PWM_OCR1A )
SET_BIT(TCCR1A , 0);
SET_BIT(TCCR1A , 1);
SET_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

    #elif(TIMER1_MODE == TIMER1_PHASE_FREQUENCT_PWM_ICR1 )
CLR_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);
    #elif(TIMER1_MODE == TIMER1_PHASE_FREQUENCT_PWM_OCR1A )
SET_BIT(TCCR1A , 0);
CLR_BIT(TCCR1A , 1);
CLR_BIT(TCCR1B , 3);
SET_BIT(TCCR1B , 4);

	#endif
	

	
/*******************  TIMER1_COMPARE_EVENT ***********************************
 * Modes used when using wave generator (output on OC1A,OC1B pin)            *
 * these modes state what will happen on OC1A / OC1B pin when the match      *
 * happens between these registers (OSR1A and TCNT1)/(OSR1B and TCNT1).      *
 *																		     *
 * (00)  the  (OC1A)/(OC1B)  pin  operates  as  an  I/0  port.    		     *
 *																		     *
 * (01) Toggle (OC1A) PIN on compare match IN MODE 15 AND				     *
 * WILLL BE DISCONNECTED IN THE OTHER MODES(Normal I/O port) .			     *
 * BUT : IN Channel B >> Normal port operation, OC I B disconnected.		 *
 *																			 *
 * (10) the waveform generator clears the (OC1A)/(OC1B) pin whenever compare *
 * match occurs(non-inverted)AND, Set (OC1A)/(OC1B) at Top					 *
 *(the beginning is high) so it is good when we need 100% duty cycle.		 *
 *																			 *
 * (11) the waveform generator set the (OC1A)/(OC1B) pin whenever compare	 *
 * match occurs( inverted )AND, Clear (OC1A)/(OC1B) at Top					 *
 * (the beginning is low) so it is good when we need 0% duty cycle.          *
 * ***************************************************************************/


//Compare Output Mode for  Channel A
	#if(TIMER1_COMPARE1A_EVENT == TIMER1_NO_ACTION)
		CLR_BIT(TCCR1A , 6);
		CLR_BIT(TCCR1A , 7);
	#elif(TIMER1_COMPARE1A_EVENT == TIMER1_TOGGLE)
		SET_BIT(TCCR1A , 6);
		CLR_BIT(TCCR1A , 7);
	#elif(TIMER1_COMPARE1A_EVENT == TIMER1_CLEAR )
		CLR_BIT(TCCR1A , 6);
		SET_BIT(TCCR1A , 7);
	#elif(TIMER1_COMPARE1A_EVENT == TIMER1_SET )
		SET_BIT(TCCR1A , 6);
		SET_BIT(TCCR1A , 7);
	#endif


//Compare Output Mode for  Channel B
			#if(TIMER1_COMPARE1B_EVENT == TIMER1_NO_ACTION)
				CLR_BIT(TCCR1B , 4);
				CLR_BIT(TCCR1B , 5);
			#elif(TIMER1_COMPARE1B_EVENT == TIMER1_TOGGLE)
				SET_BIT(TCCR1B , 4);
				CLR_BIT(TCCR1B , 5);
			#elif(TIMER1_COMPARE1B_EVENT == TIMER1_CLEAR )
				CLR_BIT(TCCR1B , 4);
				SET_BIT(TCCR1B , 5);
			#elif(TIMER1_COMPARE1B_EVENT == TIMER1_SET )
				SET_BIT(TCCR1B , 4);
				SET_BIT(TCCR1B , 5);
			#endif
		
		
	/*Disable Interrupts*/
	CLR_BIT(TIMSK , 2);
	CLR_BIT(TIMSK , 3);
	CLR_BIT(TIMSK , 4);
	CLR_BIT(TIMSK , 5);
	/*CLR FLAGS*/
	SET_BIT(TIFR , 2);
	SET_BIT(TIFR , 3);
	SET_BIT(TIFR , 4);
	SET_BIT(TIFR , 5);
	/*CLR register*/
	TCNT1H = 0 ;
	TCNT1L = 0 ;
	OCR1BH = 0 ;
	OCR1BL = 0 ;
	OCR1AH = 0 ;
	OCR1AL = 0 ;
	ICR1H = 0 ;
	ICR1L = 0 ;

}//end TIMER1_void_Init()


/*******************  SetTimerRegister **********************
* here you can preload a value in TCNT1 from 0 ­ 65,535     *
*************************************************************/
void TIMER1_void_SetTimerRegister_TCNT1(u16 Copy_u16_Value)
{
	TCNT1H = (Copy_u16_Value >> 8);
	TCNT1L = (Copy_u16_Value & 0x00FF) ;

}//end TIMER1_void_SetTimerRegister()


/*******************  SetCompareValue **************************
* here you can set a value in OCR1A from ( 0 - 65,535 ) in     *
* order to compare with TCNT1 OR BE THE TOP.                   *
****************************************************************/

void TIMER1_void_SetCompareValue_OCR1A(u16 Copy_u16_Value)
{

/*To do a 16-bit write, the high byte must be written before the low byte.
 *  For a 16-bit read, the low byte must be read before the high byte.*/
	OCR1AH = (Copy_u16_Value >> 8) ;
	OCR1AL =  (Copy_u16_Value & 0x00FF) ;

}//end TIMER1_void_SetCompareValue_OCR1A()


/*******************  SetCompareValue **************************
* here you can set a value in OCR1B from ( 0 - 65,535 ) in     *
* order to compare with TCNT1 OR BE THE TOP.				   *
****************************************************************/
void TIMER1_void_SetCompareValue_OCR1B(u16 Copy_u16_Value)
{
/*To do a 16-bit write, the high byte must be written before the low byte.
 For a 16-bit read, the low byte must be read before the high byte.*/
	OCR1BH = (Copy_u16_Value >> 8) ;
	OCR1BL = (Copy_u16_Value & 0x00FF) ;

}//end TIMER1_void_SetCompareValue_OCR1B()


/*******************  SetCompareValue ****************************
* here you can set a value in ICR1 from ( 0 - 65,535) in order to*
* BE THE TOP													 *
******************************************************************/
void TIMER1_void_SetCompareValue_ICR1(u16 Copy_u16_Value)
{
/*To do a 16-bit write, the high byte must be written before the low byte.
 *  For a 16-bit read, the low byte must be read before the high byte.*/
	ICR1H =  (Copy_u16_Value >> 8) ;
	ICR1L =   (Copy_u16_Value & 0x00FF) ;

}//end TIMER1_void_SetCompareValue_ICR1()



/*******************  Enable overflow interrupt  *****************
*    Timer/Counter1, Output Compare A Match Interrupt Enable     *
*    OCF1A Flag is raised									     *
******************************************************************/
void TIMER1_void_EnableInterrupt_COMPA(void)
{
	SET_BIT(TIMSK , 4);
	SET_BIT(SREG , 7); //enable global interrupt
}//end TIMER1_void_EnableInterrupt_COMPA()


/*******************  Disable overflow interrupt  **************
* Timer/Counter1, Output Compare A Match Interrupt Disable     *
****************************************************************/

void TIMER1_void_DisableInterrupt_COMPA(void)
{
	CLR_BIT(TIMSK , 4);
}//end TIMER1_void_DisableInterrupt_COMPA()

/*******************  Enable overflow interrupt  ***************
*    Timer/Counter1, Output Compare B Match Interrupt Enable   *
*    OCF1B Flag is raised									   *
****************************************************************/

void TIMER1_void_EnableInterrupt_COMPB(void)
{
	SET_BIT(TIMSK , 3);
	SET_BIT(SREG , 7); //enable global interrupt
}//end TIMER1_void_EnableInterrupt_COMPB()


/*******************  Disable overflow interrupt  **************
* Timer/Counter1, Output Compare B Match Interrupt Disable     *
****************************************************************/

void TIMER1_void_DisableInterrupt_COMPB(void)
{
	CLR_BIT(TIMSK , 3);
}//end TIMER1_void_DisableInterrupt_COMPB()



/*******************  Enable overflow interrupt  ***************
*    Timer/Counter1 Interrupt Enable
*    TOV1 Flag is raised (TCNT1 overflow)
****************************************************************/

void TIMER1_void_EnableInterrupt_TCNT1(void)
{
	SET_BIT(SREG , 7); //enable global interrupt
	SET_BIT(TIMSK , 2);

}//end TIMER1_void_EnableInterrupt_TCNT1()


/*******************  Disable overflow interrupt  **************
* Timer/Counter1,  Interrupt Disable     *
****************************************************************/

void TIMER1_void_DisableInterrupt_TCNT1(void)
{
	CLR_BIT(TIMSK , 2);
}//end TIMER1_void_DisableInterrupt_TCNT1()

/****************************************************************/
/*************  Enable Timer1 By setting the prescaler  *********
****************************************************************/

void TIMER1_void_Enable(u8 Copy_u8_Prescaler)
{
    /*reset the first three bits of TCCR1B to prepare them to write
	  the new value in them (Bit masking) */
	TCCR1B &= (0b11111000);

	/* write the first three bits(Bit masking) */
	TCCR1B |= Copy_u8_Prescaler;


	/* if the prescaler 6 of 7 that mean it works as counter
	   so make pin T1 as input to be the clock source */

	if((Copy_u8_Prescaler == 6) || (Copy_u8_Prescaler == 7) )
	   {
	     DIO_void_SetPinDirection(DIO_PORTB,PIN1,IN,PULLUP);
	   }

}//end TIMER1_void_Enable()


/****************************************************************/
/***********  Disable Timer By clearing  the prescaler **********
****************************************************************/

void TIMER1_void_Disable(void)
{
	//clear the first three bits
	TCCR1B &= (0b11111000);
}//end TIMER1_void_Disable()


/***********************************************************/
/*******************  CallBack for Overflow ****************/
/***********************************************************/

void TIMER1_void_Set_Overflow_CallBack(void (*Copy_ptr) (void) )
{
// set the address of your function to a pointer(pointer to function)
	TIMER1_TOV1_CallBack = Copy_ptr ;
}//end TIMER1_void_Set_Overflow_CallBack()


/************************************************************/
/*******************  CallBack for COMPA    *****************/
/************************************************************/
void TIMER1_void_Set_COMPA_CallBack(void (*Copy_ptr) (void) )
{
// set the address of your function to a pointer(pointer to function)
	TIMER1_COMPA_CallBack = Copy_ptr ;

}//end TIMER1_void_Set_COMPA_CallBack()


/************************************************************/
/*******************  CallBack for COMPB  *******************/
/************************************************************/
void TIMER1_void_Set_COMPB_CallBack(void (*Copy_ptr) (void) )
{
// set the address of your function to a pointer(pointer to function)
	TIMER1_COMPB_CallBack = Copy_ptr ;
	
}//end TIMER1_void_SetCTCCallBack()


/************************************************************/
/*******************  CallBack for CAPTURE  *****************/
/************************************************************/
void TIMER1_void_Set_Capture_CallBack(void (*Copy_ptr) (void) )
{
// set the address of your function to a pointer(pointer to function)
	TIMER1_Capture_CallBack = Copy_ptr ;

}//end TIMER1_void_Set_Capt_CallBack()



/************************************************************/
/*******************  Timer1 CAPTURE unit Enable ************/
/************************************************************/
void TIMER1_void_Enable_CaptureUnit_Interrupt(void)
{

	SET_BIT(SREG , 7); /*enable global interrupt*/
	SET_BIT(TIMSK , 5); /*enable input capture interrupt*/
	DIO_void_SetPinDirection(DIO_PORTD,PIN6,IN,PULLUP);

}//end TIMER1_void_Enable_CaptureUnit()

/*************************************************************/
/*******************  Timer1 CAPTURE unit Disable ************/
/*************************************************************/
void TIMER1_void_Disable_CaptureUnit_Interrupt(void)
{

	CLR_BIT(TIMSK , 5); /*Disable input capture interrupt*/
}//end TIMER1_void_Disable_CaptureUnit()


/************************************************************/
/*******************  Timer1 Input Capture Edge Rising ******/
/************************************************************/
void TIMER1_void_CaptureEdge_Rising(void)
{

	SET_BIT(TCCR1B , 6); //rising edge

}//end TIMER1_void_CaptureEdge_Rising()


/************************************************************/
/******************  Timer1 Input Capture Edge Falling ******/
/************************************************************/
void TIMER1_void_CaptureEdge_Falling(void)
{

	CLR_BIT(TCCR1B , 6); //falling edge


}//end TIMER1_void_CaptureEdge_Falling()

/************************************************************/
/******************  Timer1 Get Capture Value ***************/
/************************************************************/
u16 TIMER1_u16_GetCaptureValue_ICR1(void)
{

	u8 Loc_LowByte_ICR1L = ICR1L;
	u8 Loc_HighByte_ICR1H = ICR1H;

	return ( (Loc_LowByte_ICR1L) | ( Loc_HighByte_ICR1H << 8 ) );

}//end TIMER1_void_CaptureEdge_Falling()


/************************************************************/
/******************  Timer1 Get Timer Value *****************/
/************************************************************/
u16 TIMER1_u16_GetTimerValue_TCNT1(void)
{

	u8 Loc_LowByte_TCNT1L = TCNT1L;
	u8 Loc_HighByte_TCNT1H = TCNT1H;

	return ( (Loc_LowByte_TCNT1L) | ( Loc_HighByte_TCNT1H << 8 ) );

}//end TIMER1_void_CaptureEdge_Falling()


/*********************************************************************/
/************************ISRs*****************************************/
/*********************************************************************/
/*here is the address of the function that you want to execute in    *
* case of the TIMER1 overflow are fired, so the function in this     *
* address will be executed when the interrupt happens                *
**********************************************************************/
/* name of the ISR vector exist in the data sheet page 42*/

ISR(TIMER1_OVF_vect)
{
	//pointer points to a function
	TIMER1_TOV1_CallBack();
}


ISR(TIMER1_COMPA_vect)
{
	//pointer points to a function
	TIMER1_COMPA_CallBack();
}


ISR(TIMER1_COMPB_vect)
{
	//pointer points to a function
	TIMER1_COMPA_CallBack();
}

ISR(TIMER1_CAPT_vect)
{
	//pointer points to a function
	TIMER1_Capture_CallBack();
}
