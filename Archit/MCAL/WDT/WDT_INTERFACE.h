/*
 * WATCHDOG_INTERFACE.h
 *
 *  Created on: Oct 12, 2019
 *      Author: MilleR
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_



/* this function takes one value to set the prescaler
************* Available values : ******************
_17.1_ms
_34.3_ms
_68.5_ms
_0.14_s
_0.27_s
_0.55_s
_1.1_s
_2.2_s
 */
void WDT_void_Enable(u8 Copy_u8_Prescaler);

/*Reset watchdog and start counting from the degainning*/
void WDT_void_Reset(void);

/*Disble watchdog  timer*/
void WDT_void_Disable(void);



#endif /* WDT_INTERFACE_H_ */
