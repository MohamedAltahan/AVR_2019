/****************************************************************/
/*   Author             :    Mohamed Altahan 				    */
/*	 Date 				:    23 OCT 2019 						*/
/*	 Version 			:    1.0V 							 	*/
/*	 Description 		:    CONFIGURATION for USART 	    	*/
/****************************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_


#define FREQ_CPU				8000000


/****************************************************************/
/**          Please Enter the Operation Mode					*/
/** 		   MODE_OF_OPERATION can be : 						*/
/*					    					ASYNCHRONOUS 		*/
/*						    				SYNCHRONOUS 		*/
/****************************************************************/

#define MODE_OF_OPERATION	ASYNCHRONOUS


/****************************************************************/
/**         For using  Speed Operation the Mode of Operation	*/
/**							MUST be ASYNCHRONOUS				*/
/****************************************************************/
/**         Please Enter the Speed Operation					*/
/** 		   Speed Operation can be : 						*/
/*					    				NORMAL_SPEED_MODE 		*/
/*						    			DOUBLE_SPEED_MODE		*/
/****************************************************************/

#define SPEED_OPERATION		NORMAL_SPEED_MODE

/****************************************************************/
/**             Enter the Frame Size						*/
/** 		   FRAME SIZE can be : 								*/
/*					    			5 				 	     	*/
/*						    		6 					    	*/
/*									7 					    	*/
/*									8 					     	*/
/*									9 					        */
/*                                        Bits                	*/
/****************************************************************/

#define FRAME_SIZE			8


/****************************************************************/
/**                  Enter the Baud Rate						*/
/****************************************************************/

#define BAUD_RATE			9600

/****************************************************************/
/**         		    Enter the Parity Mode					*/
/** 	    	   		PARITY_MODE can be : 					*/
/*					    			DISABLED 					*/
/*						    		EVEN 						*/
/*							    	ODD							*/
/****************************************************************/

#define PARITY_MODE			DISABLED

/****************************************************************/
/**                Enter the Number of Stop Bits				*/
/** 		        STOP_BIT_SELECT can be : 	     			*/
/*					    				ONE_BIT 				*/
/*						    			TWO_BIT					*/
/****************************************************************/

#define STOP_BIT_SELECT		ONE_BIT

/****************************************************************/
/**            For using  Clock Polarity the Mode of Operation	*/
/**							MUST be SYNCHRONOUS					*/
/****************************************************************/
/*	UCPOL = 0 Rising Edge (Transmitted) Falling Edge (Received)	*/
/*	UCPOL = 1 Falling Edge (Transmitted) Rising Edge (Received) */
/****************************************************************/
/**      Please Enter the Clock Polarity					*/
/** 		   CLOCK_POLARITY can be : 							*/
/*					    				RISING			 		*/
/*						    			FALLING					*/
/****************************************************************/

#define CLOCK_POLARITY		RISING
#endif /* USART_CONFIG_H_ */
