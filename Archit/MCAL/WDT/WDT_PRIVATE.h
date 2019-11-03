/*
 * WATCHDOG_PRIVATE.h
 *
 *  Created on: Oct 12, 2019
 *      Author: MOHAMED ALTAHAN
 */

#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

/*----------------------------------------------------*/
//This regiser configer WDT
#define WDTCR     *((volatile u8*)0x41)
/*----------------------------------------------------*/

#define _17.1_ms		0
#define _34.3_ms  		1
#define _68.5_ms		2
#define _0.14_s			3
#define _0.27_s			4
#define _0.55_s			5
#define _1.1_s			6
#define _2.2_s			7

/*----------------------------------------------------*/


#endif /* WDT_PRIVATE_H_ */
