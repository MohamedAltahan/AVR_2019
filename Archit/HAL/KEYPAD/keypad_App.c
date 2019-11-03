#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "Dio_Interface.h"

#include "Keypad_interface.h"

#include "avr/delay.h"

/*

 -rows set as inputs( inernal pullup resistors are used,
  so all row pins are high in normal case )
 
 -column set as outputs
 
 
       (inputs)
         pin4 <<----|----|----|----|
         pin5 <<----|----|----|----|
         pin6 <<----|----|----|----|
         pin7 <<----|----|----|----|
		            ^    ^    ^    ^
                  pin0 pin1 pin2 pin3 (outputs)
				
the applied sequence to the column >> ( 0111 , 1011 , 1101 ,1110 ) , 

then check the input pins which one is low 


*/



static const u8 u8KeypadValues[4][4] = {

{  1,  2,  3, 4  },
{  5,  6,  7, 8  },
{  9, 10, 11, 12 },
{ 13, 14, 15, 16 }

};


/*********************************************************/
/*********************intialization***********************/
/*********************************************************/
void KEYPAD_vidInit(void) {

	// set Columns as output 
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN0, DIO_U8_DIR_OUT);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN1, DIO_U8_DIR_OUT);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN2, DIO_U8_DIR_OUT);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN3, DIO_U8_DIR_OUT);
	
	// make all the output pins high
	DIO_vidSetPinValue(KEYPAD_U8_PORT, DIO_U8_PIN0, DIO_U8_HIGH);
	DIO_vidSetPinValue(KEYPAD_U8_PORT, DIO_U8_PIN1, DIO_U8_HIGH);
	DIO_vidSetPinValue(KEYPAD_U8_PORT, DIO_U8_PIN2, DIO_U8_HIGH);
	DIO_vidSetPinValue(KEYPAD_U8_PORT, DIO_U8_PIN3, DIO_U8_HIGH);

	//set Rows as input, and all pullup resistors are active by default
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN4, DIO_U8_DIR_IN);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN5, DIO_U8_DIR_IN);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN6, DIO_U8_DIR_IN);
	DIO_vidSetPinDirection(KEYPAD_U8_PORT, DIO_U8_PIN7, DIO_U8_DIR_IN);
	
}//end KEYPAD_vidInit()


/*********************************************************/
/*****************get the pressed key*********************/
/*********************************************************/
u8 Keypad_u8GetKey(void) {

	u8 Loc_u8Key = KEY_NOTPRESS;
	
    //executed 4 sequences >> ( 0111 , 1011 , 1101 ,1110 )
	//and check the 4-input pins within each sequence
	for (u8 Loc_u8Col = 0; Loc_u8Col < 4; Loc_u8Col++) 
	{
		//Active the Sequence
		DIO_vidSetPinValue(KEYPAD_U8_PORT, Loc_u8Col, DIO_U8_LOW);
		
		// check the 4-input pins within each sequence
		for (u8 Loc_u8Row = 4; Loc_u8Row < 8 ; Loc_u8Row++) 
		{
			//check if one of the 4-input pins(pin4 to pin7) is low
            // this means that one switch of this column is pressed
			if ( !(DIO_u8GetPinValue(KEYPAD_U8_PORT, Loc_u8Row)) )
			      //because of bouncing  
                  _delay_ms(10);
            //Check again to ensure that the is really pressed				  
			if ( !(DIO_u8GetPinValue(KEYPAD_U8_PORT, Loc_u8Row)) ) 
			{
				// subtract 4 to get the row(0 to 3)				
				Loc_u8Key = u8KeypadValues[Loc_u8Row - 4][Loc_u8Col];
				
                // stay here while the key is being peressed
				while (!DIO_u8GetPinValue(KEYPAD_U8_PORT, Loc_u8Row)); 
				
			}// end if
		}//end for

		//make the pin high again to use another sequence 
		DIO_vidSetPinValue(KEYPAD_U8_PORT, Loc_u8Col, DIO_U8_HIGH);
		
		
		
	}//end for

	return Loc_u8Key;

}// end Keypad_u8GetKey()
