/********************************************/
/* Author   : MOHAMED ALTAHAN               */
/* Date     : 29 AUG 2019                   */
/* Version  : V1  							*/
/* Description : User interface for DIO pins*/
/********************************************/
#ifndef  DIO_INTERFACE_H_
#define  DIO_INTERFACE_H_

/********************************************/
/* this file has 6 functions                */
/* 1- set the pins as input or output       */
/* 2- set the pins as HIGH OR LOW           */
/* 3- get the pin value and return its value*/
/* 4- Set Ports Direction                   */
/* 5- SET ports value                       */ 
/* 6- Get ports value and return its value  */
/********************************************/



//================= prototypes for pins functions ======================*/

/*1*/
/**********************************************************************/
/*this function determine the pin direction and takes four parameters */ 
/* First is port ID which is :										  */
/*  DIO_PORTA 														  */   		
/*  DIO_PORTB 														  */			
/*  DIO_PORTC 														  */			
/*  DIO_PORTD 														  */
/* Second is pin number which is :									  */
/*  PIN0															  */
/*  PIN1															  */				
/*  PIN2															  */				
/*  PIN3															  */				
/*  PIN4															  */				
/*  PIN5															  */				
/*  PIN6															  */				
/*  PIN7															  */
/* Third is pin direction which is :								  */
/*  IN																  */
/*  OUT																  */	
/* Fourth is active pullup resistor or not :						  */
/*  PULLUP															  */             
/*  NON    															  */             
/**********************************************************************/
void DIO_void_SetPinDirection(u8 Cpy_u8PortId , u8 Cpy_u8PinNo , u8 Cpy_u8PinDir ,u8 Cpu_u8PinPull);


/*2*/
/**********************************************************************/
/*this function determine the pin value(HIGH or LOW) and takes        */
/*three parameters                                                    */
/*first and second like the previous function                         */
/*Third is the value of the pin which is :                            */
/*  HIGH                                                              */     
/*  LOW                                                               */ 
/**********************************************************************/
void DIO_void_SetPinValue(u8 Cpy_u8PortId , u8 Cpy_u8PinNo , u8 Cpy_u8PinValue);

/*3*/
/**********************************************************************/
/*this function Get the pin value(HIGH or LOW) and takes              */
/*two parameters like the first function                              */
/**********************************************************************/
u8 DIO_u8_GetPinValue(u8 Cpy_u8PortId , u8 Cpy_u8PinNo);

/*4*/
/*======================== prototypes for port functions ===============*/
/***********************************************************************/
/*this function determine the PORT direction and takes three parameters*/
/* First is port ID (Like in the first function)                       */
/* Second is port direction(Like in the first function)                */
/* Thrid is active pullup resistor or not (Like in the first function) */ 
/***********************************************************************/
void DIO_void_SetPortDirection(u8 Cpy_u8PortId , u8 Cpy_u8ProtDir , u8 Cpy_u8PinPull);

/*5*/
/**********************************************************************/
/*this function determine the PORT value(HIGH or LOW) and takes       */
/*two parameters                                                      */
/*first is port ID like the previous function(like the first function)*/
/*second is the value of the PORT(like the second function)           */
/**********************************************************************/
void DIO_void_SetPortValue(u8 Cpy_u8PortId , u8 Cpy_u8PortValue);


/*6*/
/***********************************************************************/
/*this function Get the PORT value(HIGH or LOW) and takes one parameter*/
/* Which is PORT ID (like the first function)						   */
/***********************************************************************/
u8 DIO_u8_GetPortValue(u8 Cpy_u8PortId);



#endif /* DIO_INTERFACE_H_ */
