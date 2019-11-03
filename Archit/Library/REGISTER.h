
#ifndef _DIO_REG_H
#define _DIO_REG_H

/* ********************* DIO ****************************** */

/* Group A Registers */
#define PORTA  *((volatile u8*)0x3B)
#define DDRA   *((volatile u8*)0x3A)
#define PINA   *((volatile u8*)0x39)

/* Group B Registers */
#define PORTB  *((volatile u8*)0x38)
#define DDRB   *((volatile u8*)0x37)
#define PINB   *((volatile u8*)0x36)

/* Group C Registers */
#define PORTC  *((volatile u8*)0x35)
#define DDRC   *((volatile u8*)0x34)
#define PINC   *((volatile u8*)0x33)

/* Group D Registers */
#define PORTD *((volatile u8*)0x32)
#define DDRD  *((volatile u8*)0x31)
#define PIND  *((volatile u8*)0x30)

/* ********************* ADC ****************************** */

#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL    *((volatile u8*)0x24)
#define SFIOR   *((volatile u8*)0x50)

/* ********************* External Interrupt *************** */

#define SREG  	 *((volatile u8*)0x5F)
#define MCUCR    *((volatile u8*)0x55)
#define MCUCSR   *((volatile u8*)0x54)
#define GICR     *((volatile u8*)0x5B)
#define GIFR     *((volatile u8*)0x5A)



#endif
