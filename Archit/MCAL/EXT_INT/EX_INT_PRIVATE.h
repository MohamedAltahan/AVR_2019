#ifndef _EX_INT_PRIVATE_H_
#define _EX_INT_PRIVATE_H_



/* ********************* External Interrupt Register *************** */

#define SREG  	 *((volatile u8*)0x5F)
#define MCUCR    *((volatile u8*)0x55)
#define MCUCSR   *((volatile u8*)0x54)
#define GICR     *((volatile u8*)0x5B)
#define GIFR     *((volatile u8*)0x5A)

/*---------------------------------------------------------------------*/

#define INT0_LOW_LEVEL           0
#define INT0_ON_CHANGE           1
#define INT0_FALLING_EDGE        2
#define INT0_RISING_EDGE         3
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/

#define INT1_LOW_LEVEL           0
#define INT1_ON_CHANGE           4
#define INT1_FALLING_EDGE        8
#define INT1_RISING_EDGE         12
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/

#define INT2_FALLING_EDGE        0
#define INT2_RISING_EDGE         64
/*---------------------------------------------------------------------*/

#define PULLUP                 1
#define NON                    0


#endif
