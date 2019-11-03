#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "avr/delay.h"


#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"

 /* this driver latch the 4-high bits of a given byte
  so you have to divide your byte into two parts and send
  the high four bits then shift the 4-low bits in the place
  of the the four high bits  and send them  in Successive manner */

/*when you write any command you must divide it into two commands
 * in successive manner >>first cmd is  the left digit then the 
 * second cmd is the right digit of the hex number.  */




/***************************************************/
/**************** LCD Initialization ***************/
/***************************************************/
void LCD_vidInit()

{   //delay time given in data sheet
	LCD_vidDelay_ms(30);
	
	//SET THE pins AS OUTPUT
	DIO_void_SetPinDirection(LCD_DATA_PORT , RS , OUT);
	DIO_void_SetPinDirection(LCD_DATA_PORT , EN , OUT);
	DIO_void_SetPinDirection(LCD_DATA_PORT , D4 , OUT);
	DIO_void_SetPinDirection(LCD_DATA_PORT , D5 , OUT);
	DIO_void_SetPinDirection(LCD_DATA_PORT , D6 , OUT);
	DIO_void_SetPinDirection(LCD_DATA_PORT , D7 , OUT);
	
	//set RS to zero
	DIO_void_SetPinValue(LCD_DATA_PORT , RS , LOW);
	//set enable to zero
	DIO_void_SetPinValue(LCD_DATA_PORT , EN , LOW);
	
    //some commands for intializing from data sheet
	LCD_vidWriteCmd(0x20);
	LCD_vidWriteCmd(0x20);
	LCD_vidWriteCmd(0x80);
	LCD_vidDelay_us(40);
	LCD_vidWriteCmd(0x00);
	LCD_vidWriteCmd(0xC0);
	LCD_vidDelay_us(40);
	LCD_vidWriteCmd(0x00);
	LCD_vidWriteCmd(0x10);
	LCD_vidDelay_ms(2);
	LCD_vidWriteCmd(0x00);
	LCD_vidWriteCmd(0x60);

}//end of LCD_vidInitialization()


/***************************************************/
/**************** Write command ********************/
/***************************************************/
void LCD_vidWriteCmd(u8 Cpy_u8Cmd)
{
	//set RS to zero to write command
	DIO_void_SetPinValue(LCD_DATA_PORT,RS,LOW);

	//write the command on the port
	LCD_vidWriteData(Cpy_u8Cmd);

	// Send The EN pulse to latch the command
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,HIGH);
	LCD_vidDelay_us(1);
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,LOW);

	LCD_vidDelay_ms(2);

}//end of LCD_vidWriteCmd()


/***************************************************/
/******************* Write Data ********************/
/***************************************************/
void LCD_vidWriteData(u8 Cpy_u8Data)
{
	// write the 4-high bits of a given byte on 4-pins of the port

	if(Cpy_u8Data & 16) //to get the value of bit no.4
	      //put the value of the bit on the pin
	      DIO_void_SetPinValue(LCD_DATA_PORT,D4,HIGH);//send HIGH on the pin
	  else
		  DIO_void_SetPinValue(LCD_DATA_PORT,D4,LOW);// send LOW on the pin

	  if(Cpy_u8Data & 32)//to get the value of bit no.5
		  DIO_void_SetPinValue(LCD_DATA_PORT,D5,HIGH);
	  else
		  DIO_void_SetPinValue(LCD_DATA_PORT,D5,LOW);

	  if(Cpy_u8Data & 64)//to get the value of  bit no.6
		  DIO_void_SetPinValue(LCD_DATA_PORT,D6,HIGH);
	  else
		  DIO_void_SetPinValue(LCD_DATA_PORT,D6,LOW);

	  if(Cpy_u8Data & 128)//to get the value of bit no.7
		  DIO_void_SetPinValue(LCD_DATA_PORT,D7,HIGH);
	  else
		  DIO_void_SetPinValue(LCD_DATA_PORT,D7,LOW);


}//end of LCD_vidWriteData()


/***************************************************/
/******************* Write character ***************/
/***************************************************/
void LCD_vidWriteChar(u8 Cpy_u8Data)
{  //RS IS HIGH >>>> WRITE DATA
	DIO_void_SetPinValue(LCD_DATA_PORT,RS,HIGH);


	//get the high 4-bits
	LCD_vidWriteData(Cpy_u8Data & 0xF0);

	// EN PULSE TO LATCH THE DATA
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,HIGH);
	LCD_vidDelay_us(1);
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,LOW);


	//get the low 4-bits and shift them to be the 4-high bits
	LCD_vidWriteData(( Cpy_u8Data & 0x0F ) << 4 );

	// EN PULSE TO LATCH THE DATA
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,HIGH);
	LCD_vidDelay_us(1);
	DIO_void_SetPinValue(LCD_DATA_PORT,EN,LOW);
}


/***************************************************/
/******************* Write string*******************/
/***************************************************/

void LCD_vidWriteString( u8 * Ptr_u8String)
{
	for(u8 counter = 0 ; Ptr_u8String[counter] != '\0' ; counter++)
	{
		LCD_vidWriteChar(Ptr_u8String[counter]);
	}
}//end LCD_vidWriteString()


/***************************************************/
/******************* delay *************************/
/***************************************************/
void LCD_vidDelay_ms(u16 Cpy_u16Ticks)
{
	_delay_ms(Cpy_u16Ticks);
}
void LCD_vidDelay_us(u16 Cpy_u16Ticks)
{
	_delay_us(Cpy_u16Ticks);
}


/***************************************************/
/******************* shift *************************/
/***************************************************/
void LCD_vidShiftLeft()
{
	//0x18 for shift left
   LCD_vidWriteCmd(0x10);
   LCD_vidWriteCmd(0x80);
  
}
void LCD_vidShiftRight()
{
	//0x1C for shift right
   LCD_vidWriteCmd(0x10);
   LCD_vidWriteCmd(0xC0);
   
}

/***************************************************/
/******************* GOTO  *************************/
/***************************************************/

void LCD_vidGoTo(u8 Cpy_u8Row , u8 Cpy_u8Column)
{
  if(Cpy_u8Row == 0)
  {
	/* first send the 4-high bits then send the 4-low bits*/
	//0x80 is the base where we start from data sheet
	LCD_vidWriteCmd(( 0x80 + Cpy_u8Column ));
	LCD_vidWriteCmd(( 0x80 + Cpy_u8Column ) << 4  );
  }
  else if(Cpy_u8Row == 1)
  {
	//0xC0 = 0x80 + 0x40
	// 0x40 is the beginning of the second row
	LCD_vidWriteCmd(( 0xC0 + Cpy_u8Column ));
	LCD_vidWriteCmd(( 0xC0 + Cpy_u8Column )<<4 );
  }//end LCD_vidGoTo()

}


/***************************************************/
/******************* clear  ************************/
/***************************************************/
void LCD_vidClear()
{
	//0x01 to clear LCD
     LCD_vidWriteCmd(0x00);
	 LCD_vidWriteCmd(0x10);

	 
}//end LCD_vidClear()
