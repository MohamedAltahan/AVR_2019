/*************************************************************
 * Author   : MOHAMED ALTAHAN       			             *
 * Date     : 25 SEP 2019              		  		         *
 * Version  : V1  										     *
 * Description : User guide interface for external interrupts*
 *************************************************************/

#ifndef EX_IINT_INTERFACE_H_
#define EX_IINT_INTERFACE_H_

/*============================ initialization =========================*/

/* INITIALIZAION OF ALL EXTERNAL INERRUPTS */
void INT_void_Init(void);

/*=============================== ENABLE  =============================*/

/* ENABLE INT0*/
void INT0_void_Enable(void);
/* ENABLE INT1*/
void INT1_void_Enable(void);
/* ENABLE INT2*/
void INT2_void_Enable(void);
/*===============================  DISABLE ============================*/
/* Disable INT0*/
void INT0_void_Disable(void);
/* Disable INT1*/
void INT1_void_Disable(void);
/* Disable INT2*/
void INT2_void_Disable(void);

/*============================ TRIGGER LEVEL ==========================*/

/***********************************************************************/
/* this functions determine what will happen when an event happens     */
/*  on INT pins                                                        */
/***********************************************************************/

/****** AVAILABLE TRIGGER LEVEL CHOICES FOR INT0****************
INT0_LOW_LEVEL
INT0_ON_CHANGE               //this mode need at least 5 cycles to sense
INT0_RISING_EDGE
INT0_FALLING_EDGE
*/
void INT0_void_TriggerLevel(u8 Cpy_u8_TrigLevel);


/****** AVAILABLE TRIGGER LEVEL CHOICES FOR INT1****************
INT1_LOW_LEVEL
INT1_ON_CHANGE                  //this mode need at least 5 cycles to sense
INT1_RISING_EDGE
INT1_FALLING_EDGE
*/
void INT1_void_TriggerLevel(u8 Cpy_u8_TrigLevel);


/****** AVAILABLE TRIGGER LEVEL CHOICES FOR INT2****************
INT2_RISING_EDGE
INT2_FALLING_EDGE
*/
void INT2_void_TriggerLevel(u8 Cpy_u8_TrigLevel);


/*================================= CallBack ===========================*/

/*************************************************************************
* replace [ void(*Copy_ptr)(void) ] with the name of your function that  *
*you want to execute when the interrupt is happened >>				 	 *
*when you send the name of your function means you send the address	     *
*of the function, then you must receive it in (pointer to function).	 *
*write you own functions under the main that you want to execute when    *
*the interrupt is happened with any name you want						 *
**************************************************************************/
/* Callback for INT0 */
void INT0_vidSetCallBack( void(*Copy_ptr)(void) );
/* Callback for INT1 */
void INT1_vidSetCallBack( void(*Copy_ptr)(void) );
/* Callback for INT2 */
void INT2_vidSetCallBack( void(*Copy_ptr)(void) );



#endif /* EXTI_INTERFACE_H_ */
