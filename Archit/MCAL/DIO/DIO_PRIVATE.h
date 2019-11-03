
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

/* there is no pulldown resistor */
/*------------------ Pin Pull ----------------*/
#define PULLUP              1
#define NON                 0

/*----------------- Pin state ----------------*/
#define HIGH     1
#define LOW      0
#define ERROR    0xff


/*----------------- pin number ---------------*/
#define PIN0				0
#define PIN1				1
#define PIN2				2
#define PIN3				3
#define PIN4				4
#define PIN5				5
#define PIN6				6
#define PIN7				7

/*---------------- port number ---------------*/

#define DIO_PORTA    		0
#define DIO_PORTB			1
#define DIO_PORTC			2
#define DIO_PORTD			3

/*---------------- Direction -----------------*/
#define IN			0
#define OUT			1




#endif
