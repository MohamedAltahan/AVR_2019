#ifndef _TIMER1_PRIVATE_H
#define _TIMER1_PRIVATE_H


//Timer1/Counter1 Control  Register(A)
/* FOC1A,FOC1B : p7  Force compare  match: This  is a write-only bit,
which can  be  used while generating a wave.
Writing  1  to  it causes the wave generator to  act as
if a compare match  had  occurred.*/
#define TCCR1A  	  *((volatile u8*)0x4F)

//Timer/Counter1 Control Register (B)
#define TCCR1B        *((volatile u8*)0x4E)

//Timer/Counter1  give direct access, both for read and for write operations,
//to the Timer/Counter unit 16-bit counter.
#define TCNT1H      *((volatile u8*)0x4D)
#define TCNT1L      *((volatile u8*)0x4C)

//Output Compare Register 1 A ,The Output Compare Registers contain a 16-bit
//value that is continuously compared with the counter value (TCNT1)
#define OCR1AH     *((volatile u8*)0x4B)
#define OCR1AL     *((volatile u8*)0x4A)

//Output Compare Register 1 B ,The Output Compare Registers contain a 16-bit
//value that is continuously compared with the counter value (TCNT1)
#define OCR1BH     *((volatile u8*)0x49)
#define OCR1BL     *((volatile u8*)0x48)
//Input Capture Register 1, The Input Capture is updated with the
//counter (TCNT1) value each time an event occurs on the ICP1 pin
//(or optionally on the analog comparator output for Timer/Counter1)
#define ICR1H      *((volatile u8*)0x47)
#define ICR1L      *((volatile u8*)0x46)
//Interrupt Enable
//Timer Interrupt Mask Register
#define TIMSK      *((volatile u8*)0x59)
//contain the status of flags
#define TIFR       *((volatile u8*)0x58)

//STATUS REGISTER - HAS GLOBAL INTERRPT ENABLE -
#define SREG  	 *((volatile u8*)0x5F)

/*--------------------------------------------------------*/


#define TIMER1_NORMAL 		            0

#define TIMER1_PHASE_PWM_8BIT       	1
#define TIMER1_PHASE_PWM_9BIT       	2
#define TIMER1_PHASE_PWM_10BIT       	3

#define TIMER1_CTC_OCR1A                4

#define TIMER1_FAST_PWM_8BIT        	5
#define TIMER1_FAST_PWM_9BIT        	6
#define TIMER1_FAST_PWM_10BIT        	7

#define TIMER1_PHASE_FREQUENCT_PWM_ICR1        	8
#define TIMER1_PHASE_FREQUENCT_PWM_OCR1A        9

#define TIMER1_PHASE_PWM_ICR1       	10
#define TIMER1_PHASE_PWM_OCR1A       	11

#define TIMER1_CTC_ICR1                 12

#define TIMER1_FAST_PWM_ICR1        	14
#define TIMER1_FAST_PWM_OCR1A       	15

/*--------------------------------------------------------*/


/*--------------------------------------------------------*/
#define TIMER1_NO_ACTION	1
#define TIMER1_TOGGLE		2
#define TIMER1_SET			3
#define TIMER1_CLEAR		4

/*--------------------------------------------------------*/

#define NO_PRESCALER    			1
#define PRESCALER_8     			2
#define PRESCALER_64     			3
#define PRESCALER_256     			4
#define PRESCALER_1024     			5
#define COUNTER_FALLING_EDGE     	6
#define COUNTER_FALLING_RISING     	7

/*--------------------------------------------------------*/

#endif
