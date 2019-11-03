/********************************************/
/* Author   : MOHAMED ALTAHAN               */
/* Date     : 7 sep 2019                    */
/* Version  : V1                            */
/********************************************/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/*
       (inputs)
         pin4 <<----|----|----|----|
         pin5 <<----|----|----|----|
         pin6 <<----|----|----|----|
         pin7 <<----|----|----|----|
		            ^    ^    ^    ^
                  pin0 pin1 pin2 pin3 (outputs)
				  			  				  
*/				  

				  
#define KEYPAD_U8_PORT		DIO_U8_PORTC

#define KEY_NOTPRESS		255

void KEYPAD_vidInit(void);

u8 Keypad_u8GetKey(void);

#endif /* KEYPAD_INTERFACE_H_ */
