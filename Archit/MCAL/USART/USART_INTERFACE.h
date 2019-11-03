/****************************************************************/
/*   Author             :    Mohamed Altahan 				    */
/*	 Date 				:    23 OCT 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:  USART user interface guide           */
/****************************************************************/

#ifndef _USART_INT_H
#define _USART_INT_H
/*========================== Initialization(mandatory) ========================*/

/****************************************************************/
/* Description    :  This function used to initialize USART     */
/* you must use this function (mandatory)                       */
/****************************************************************/
void USART_void_Init();

/*============================== TX and RX state ==============================*/

/****************************************************************/
/* Description    : This function used to Enable TX and  RX 	*/
/****************************************************************/
void USART_void_Enable_TX_RX();


/****************************************************************/
/* Description    : This function used to Disable TX and  RX 	*/
/****************************************************************/
void USART_void_Disable_TX_RX();

/*====================== Transmit and Receive Data ============================*/

/****************************************************************/
/* Description    : This function used to Send Char only		*/
/****************************************************************/
/*this function must be used after USART initialized 		    */
/****************************************************************/
void USART_Transmit_8BitData( u8 data );


/****************************************************************/
/* Description    : This function used to Send String			*/
/****************************************************************/
/*this function must be used after USART initialized 		    */
/****************************************************************/
void USART_Transmit_String( u8 *Ptr_u8_String );


/****************************************************************/
/* Description    : This function used to Receive Data			*/
/****************************************************************/
/*  this function must be used after USARTinitialized 	        */
/****************************************************************/
u8 USART_Receive();


/*=============================== Interrupt ===================================*/
/****************************************************************/
/* Description    : This function used to Enable Interrupt      */
/* when the data Completely transmitted            			    */
/****************************************************************/
void USART_void_Enable_TX_Complete_Interrupt();


/****************************************************************/
/* Description    : This function used to Enable Interrupt      */
/* when the data Completely Received            			    */
/****************************************************************/
void USART_void_Enable_RX_Complete_Interrupt();


/****************************************************************/
/* Description    : This function used to Enable Interrupt      */
/* when Transmit Buffer is ready to be written again    	    */
/****************************************************************/
void USART_void_Enable_TX_Buffer_Ready_Interrupt();


/****************************************************************/
/* Description    : This function used to Disable Interrupt     */
/* of the data Completely transmitted            			    */
/****************************************************************/
void USART_void_Disable_TX_Complete_Interrupt();


/****************************************************************/
/* Description    : This function used to Disable Interrupt     */
/* of the data Completely transmitted            			    */
/****************************************************************/
void USART_void_Disable_RX_Complete_Interrupt();


/****************************************************************/
/* Description    : This function used to Disable Interrupt     */
/* of Transmit Buffer is ready to be written again    	        */
/****************************************************************/
void USART_void_Disable_TX_Buffer_Ready_Interrupt();

/*============================ Callback ======================================*/

/****************************************************************/
/* Description    : This function used to Set Receive Callback	*/
/****************************************************************/
void USART_void_Set_Receive_Callback();


/****************************************************************/
/* Description    : This function used to Set Transmit Callback	*/
/****************************************************************/
void USART_void_Set_Transmit_Callback();


/****************************************************************/
/* Description    : This function used to set Transmit Buffer  **/
/* Write Callback			                                    */
/****************************************************************/
void USART_void_Set_TransmitBuffer_Callback();

/*=============================== flags ======================================*/

/* RECEIVE COMPLETE FLAG (RXC) :
This flag bit is set when there are unread data in the receive buffer
and cleared when the receive buffer is empty( does not contain any unread data)
          in      ( Register : UCSRA, BIT : 7 ) */

/*Transmit Complete FLAG (TXC)  :
This flag bit is set when the entire frame in the transmit Shift Register has been shifted
out and there are no new data currently present in the transmit buffer (UDR). The TXC
Flag bit is automatically cleared when a transmit complete interrupt is executed
          in      ( Register : UCSRA, BIT : 6 ) */

/*USART Data Register Empty(UDRE) :
 * The UDRE Flag indicates if the transmit buffer (UDR) is ready to receive new data. If
UDRE is one, the buffer is empty, and therefore ready to be written.
           in      ( Register : UCSRA, BIT : 5 ) */


#endif	/*  End of guard   */
