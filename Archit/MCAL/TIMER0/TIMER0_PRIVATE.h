/*
 * timer.c
 *
 *  Created on: Oct 3, 2019
 *  edited on : Oct 10,2019
 *      Author: Mohamed Althan
 */
#ifndef _TIMER0_PRIVATE_H
#define _TIMER0_PRIVATE_H


//Timer/Counter Control  Register
/* FOCO : p7  Force compare  match: This  is a write-only bit,
which can  be  used while generating a wave.
 Writing  1  to  it causes the wave
generator to  act as  if a compare match  had  occurred.*/
#define TCCR0  	  *((volatile u8*)0x53)

//contain the value of timer0/counter0
//we can preload it with a value
#define TCNT0     *((volatile u8*)0x52)

//contain the value of ctc and always compare it with TCNT0.
//Output Compare Register
#define OCR0      *((volatile u8*)0x5C)

//Interrupt Enable
//Timer Interrupt Mask Register
#define TIMSK     *((volatile u8*)0x59)

//contain the status of flags

#define TIFR      *((volatile u8*)0x58)

#define SFIOR     *((volatile u8*)0x50)

//status register which can enable global interrupt or use sei() .
#define SREG     *((volatile u8*)0x5F)


/*--------------------------------------------------------------*/

#define TIMER0_NORMAL 		1
#define TIMER0_CTC 			2
#define TIMER0_FAST_PWM 	3
#define TIMER0_PHASE_PWM 	4

/*----------------------------------------------------------------*/

#define TIMER0_NO_ACTION	100
#define TIMER0_TOGGLE		12
#define TIMER0_SET			20
#define TIMER0_CLEAR		25

/*------------------------------------------------------*/


#define NO_PRESCALER    			1
#define PRESCALER_8     			2
#define PRESCALER_64     			3
#define PRESCALER_256     			4
#define PRESCALER_1024     			5
#define COUNTER_FALLING_EDGE     	6
#define COUNTER_RISING_EDGE     	7
/*------------------------------------------------------*/

#endif
