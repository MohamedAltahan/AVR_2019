/****************************************************************/
/*   Author             :    Mohamed Altahan 				    */
/*	 Date 				:    23 OCT 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    prog.c for USART				 	*/
/****************************************************************/

/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include"avr/interrupt.h"
/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/
#include "USART_INTERFACE.h"
#include "USART_CONFIG.h"
#include "USART_PRIVATE.h"



/* pointer to function used for callback*/
void (*USART_TX_Callback)  (void) ;
void (*USART_RX_Callback)  (void) ;
void (*USART_UDRE_Callback)(void);



/*************************************************************************/
/*********************** Function Implementation  ************************/
/*************************************************************************/


void USART_void_Init()
{
	//to hold baudrate value
	u16 Loc_u16_baudEquation = 0 ;

	/* you can't modify separate bit in UCSRC register, you have to write
	 * the whole byte one time, so we'll use this temp variable and in final
	 * we'll assign temp value to UCSRC */
	u8  Loc_u8_UCSRC_Temp = 0 ;

	/*	Operation mode Synchronous or Asynchronous	*/
	#if MODE_OF_OPERATION == ASYNCHRONOUS
		CLR_BIT(Loc_u8_UCSRC_Temp, 6);

	#elif MODE_OF_OPERATION == SYNCHRONOUS
		SET_BIT( Loc_u8_UCSRC_Temp , 6 );

	#endif


	/*	Parity mode Disabled or Odd or Even  */
	#if PARITY_MODE	== DISABLED
		CLR_BIT(Loc_u8_UCSRC_Temp, 4 );
		CLR_BIT(Loc_u8_UCSRC_Temp, 5 );

	#elif PARITY_MODE	== EVEN
		CLR_BIT(Loc_u8_UCSRC_Temp, 4 );
		SET_BIT( Loc_u8_UCSRC_Temp , 5 );

	#elif PARITY_MODE	== ODD
		SET_BIT( Loc_u8_UCSRC_Temp , 4 );
		SET_BIT( Loc_u8_UCSRC_Temp , 5 );

	#endif


	/*	Speed mode normal or Double	 */
	#if MODE_OF_OPERATION == ASYNCHRONOUS

          #if SPEED_OPERATION	== DOUBLE_SPEED_MODE
			SET_BIT(UCSRA, 1);

          #elif( SPEED_OPERATION == NORMAL_SPEED_MODE )
			CLR_BIT(UCSRA, 1);
          #endif
	#elif MODE_OF_OPERATION == SYNCHRONOUS
		CLR_BIT(UCSRA, 1);

	#endif

		/*  Baud rate Equation	*/
	#if MODE_OF_OPERATION == ASYNCHRONOUS
		#if SPEED_OPERATION == NORMAL_SPEED_MODE
		/* Asynchronous Normal Mode */
		Loc_u16_baudEquation = ((FREQ_CPU / (16.0 * BAUD_RATE)) - 1 );
		#elif SPEED_OPERATION == BOUBLE_SPEED_MODE
		/* Asynchronous Double Speed Mode */
		Loc_u16_baudEquation = ((FREQ_CPU / (8.0 * BAUD_RATE)) - 1 );
		#endif
	#elif MODE_OF_OPERATION == SYNCHRONOUS
			/* Synchronous (Master Mode) */
			Loc_u16_baudEquation = ((FREQ_CPU / (2.0 * BAUD_RATE)) - 1 );

	#endif

	/* Set baud rate */
	/* first put the high byte in UBRRH */
	UBRRH = ( Loc_u16_baudEquation >> 8);
	/* then put the low byte in UBRRL */
	UBRRL = Loc_u16_baudEquation;


	/*	 Character Size N-Bits	*/
	#if FRAME_SIZE	== 5
		CLR_BIT( Loc_u8_UCSRC_Temp , 1 );
		CLR_BIT( Loc_u8_UCSRC_Temp , 2 );
		CLR_BIT( UCSRB , 2 );

	#elif FRAME_SIZE == 6
		SET_BIT( Loc_u8_UCSRC_Temp , 1 );
		CLR_BIT( Loc_u8_UCSRC_Temp , 2 );
		CLR_BIT( UCSRB , 2 );

	#elif FRAME_SIZE == 7
		CLR_BIT( Loc_u8_UCSRC_Temp , 1 );
		SET_BIT( Loc_u8_UCSRC_Temp , 2 );
		CLR_BIT( UCSRB , 2 );

	#elif FRAME_SIZE == 8
		SET_BIT( Loc_u8_UCSRC_Temp , 1 );
		SET_BIT( Loc_u8_UCSRC_Temp , 2 );
		CLR_BIT( UCSRB , 2 );

	#elif FRAME_SIZE == 9
		SET_BIT( Loc_u8_UCSRC_Temp , 1 );
		SET_BIT( Loc_u8_UCSRC_Temp , 2 );
		SET_BIT( UCSRB , 2 );

	#endif



	/*	Stop bit select number One or Two Bits */
	#if STOP_BIT_SELECT	== TWO_BIT
			SET_BIT( Loc_u8_UCSRC_Temp , 3 );

	#elif STOP_BIT_SELECT == ONE_BIT
			CLR_BIT( Loc_u8_UCSRC_Temp , 3 );

	#endif

/*  clock polarity	*/
/* This bit is used for Synchronous mode only */
	#if MODE_OF_OPERATION == SYNCHRONOUS
/* Transmitted Data Changed (Output of TxD Pin) Rising XCK Edge
 * Received Data Sampled (Input on RxD Pin) Falling XCK Edge*/
		#if CLOCK_POLARITY	== RISING
			CLR_BIT( Loc_u8_UCSRC_Temp , 0 );

/* Transmitted Data Changed (Output of TxD Pin) Falling  XCK Edge
 * Received Data Sampled (Input on RxD Pin) Rising XCK Edge*/
		#elif CLOCK_POLARITY	== FALLING
			SET_BIT( Loc_u8_UCSRC_Temp , 0 );

	    #endif

	#endif


/****************************************************************/
/**              Bit 7 – URSEL: Register Select.				*/
/** 		  This bit selects between accessing the UCSRC or 	*/
/*							the UBRRH Register.					*/
/*If URSEL is zero during a write operation, the UBRRH value    */
/* will be updated.												*/
/* If URSEL is one, the UCSRC setting will be updated           */
/****************************************************************/
    /*WRITTING ONE TO  URSEL BIT*/
	SET_BIT( Loc_u8_UCSRC_Temp , 7 );

/****************************************************************/
/**             UCSRC : USART control and status Registe.		*/
/** 		  	Force Acesses to UCSRC Register because sharing */
/*				the	same I/O location with UBBRH.				*/
/****************************************************************/

	UCSRC = Loc_u8_UCSRC_Temp ;

	/*Disable Interrupts*/
	CLR_BIT(UCSRB , 7);
	CLR_BIT(TIMSK , 6);
	CLR_BIT(TIMSK , 5);
	/*Clear flags*/
	SET_BIT(UCSRA , 7);
	SET_BIT(UCSRA , 6);
	SET_BIT(UCSRA , 5);
}// end USART_void_Init()

/****************************************************************/
/**** Enable Transmitter and Receiver of USAER  *****************/
/****************************************************************/
void USART_void_Enable_TX_RX()
{
	    /* Enable transmitter */
		SET_BIT( UCSRB , 3 );
		/* 	Enable receiver	*/
		SET_BIT( UCSRB , 4 );

}//end USART_void_Enable_TX_RX()


/****************************************************************/
/*** Disable Transmitter and Receiver of USAER  *****************/
/****************************************************************/
void USART_void_Disable_TX_RX()
{
	    /* Disable transmitter */
		CLR_BIT( UCSRB , 3 );
		/* 	Disable receiver  */
		CLR_BIT( UCSRB , 4 );

}//end USART_void_Disable_TX_RX()


/******************************************************************************************/
/*               This function used to Send char only			                          */
/******************************************************************************************/
/*The USART Transmit Data Buffer Register and USART Receive Data Buffer Registers         */
/*share the same I/O address referred to as USART Data Register or UDR. The Transmit      */
/*Data Buffer Register (TXB) will be the destination for data written to the UDR Register */
/*location. Reading the UDR Register location will return the contents of the Receive Data*/
/*Buffer Register (RXB).																  */
/******************************************************************************************/
void USART_Transmit_8BitData( u8 data )
{
	/* Wait for empty transmit buffer */
	while( (GET_BIT(UCSRA,5)) == 0 );
	/* Put data into buffer, sends the data */
	UDR = data;

}//end USART_Transmit()


/**************************************************************************/
/*               This function used to Send String   			          */
/**************************************************************************/
void USART_Transmit_String( u8 *Ptr_u8_String )
{

	for(u8 counter = 0 ; Ptr_u8_String[counter] != '\0' ; counter++)
	{
		USART_Transmit_8BitData(Ptr_u8_String[counter]);
	}
}//end USART_Transmit_String()


/****************************************************************/
/* Description    : This function used to Receive Data			*/
/****************************************************************/
u8 USART_u8_Receive()
{
	/* Wait for data to be received */
	//while( GET_BIT( UCSRA , 7 ) ==0 );

	/* Get and return received data from buffer */
	return UDR;

}//end USART_u8_Receive()



/**************************************************************/
/************************  Interrupts Enable   ****************/
/**************************************************************/

/* Enable USART Transmit Complete Interrupt*/
void USART_void_Enable_TX_Complete_Interrupt()
{
  SET_BIT(SREG , 7); //enable global interrupt
  SET_BIT(UCSRB,6);
}

/* Enable USART Receive Complete Interrupt*/
void USART_void_Enable_RX_Complete_Interrupt()
{
	SET_BIT(SREG , 7); //enable global interrupt
	SET_BIT(UCSRB,7);
}

/* Enable USART Transmit Buffer Write Interrupt (when the Transmit buffer is ready
 *  to be written)  */
void USART_void_Enable_TX_Buffer_Ready_Interrupt()
{
	SET_BIT(SREG , 7); //enable global interrupt
	SET_BIT(UCSRB,5);
}


/**************************************************************/
/***********************  Interrupts Disable   ****************/
/**************************************************************/
/* Enable USART Transmit Interrupt*/
void USART_void_Disable_TX_Complete_Interrupt()
{
	CLR_BIT(UCSRB,6);
}

/* Enable USART Receive Interrupt*/
void USART_void_Disable_RX_Complete_Interrupt()
{
	CLR_BIT(UCSRB,7);
}

/* Enable USART Transmit Buffer Write Interrupt (when the buffer is ready
 *  to be written)  */
void USART_void_Disable_TX_Buffer_Ready_Interrupt()
{
	CLR_BIT(UCSRB,5);
}


/**************************************************************/
/************************   Callback   ************************/
/**************************************************************/

/* Callback when Receive new data  */
void USART_void_Set_Receive_Callback(void (* Copy_Ptr) (void))
{
	USART_RX_Callback = Copy_Ptr;
}

/* Callback when Transmitted data is done  */
void USART_void_Set_Transmit_Callback( void (* Copy_Ptr) (void))
{
	USART_TX_Callback = Copy_Ptr;
}

/* Callback when Transmit Buffer is ready to be Written  */
void USART_void_Set_TransmitBuffer_Callback( void (*Copy_Ptr) (void))
{
	USART_UDRE_Callback = Copy_Ptr;
}


/**************************************************************/
/************************       ISRs   ************************/
/**************************************************************/


/* Executed when Receive a new data*/
ISR(USART_RXC_vect)
{
	//pointer points to a function
	USART_RX_Callback();
}

/* Executed when the transmitted data is done */
ISR(USART_TXC_vect)
{
	//pointer points to a function
	USART_TX_Callback();
}

/* transmit buffer is Ready to be written with new data */
    ISR(USART_UDRE_vect)
{
	//pointer points to a function
	USART_UDRE_Callback();
}



/****************************************************************************/
/************************************* END OF PROGRAM ***********************/
/****************************************************************************/
