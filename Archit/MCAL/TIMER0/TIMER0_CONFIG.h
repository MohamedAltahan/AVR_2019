/*
 * timer.c
 *
 *  Created on: Oct 3, 2019
 *  edited on : Oct 10,2019
 *      Author: Mohamed Althan
 */
#ifndef _TIMER0_CONFIG_H
#define _TIMER0_CONFIG_H


//-------------------------------------------------------------
/*
 * Modes of the timer/counter

TIMER0_NORMAL
TIMER0_CTC        ---->( clear on compare)
TIMER0_FAST_PWM
TIMER0_PHASE_PWM

(note : [TIMER0_CTC and TIMER0_NORMAL] can work as timer or counter
it depends on the source of the clock >>> input on T0 pin)

(note : [TIMER0_FAST_PWM and TIMER0_PHASE_PWM] can work as
wave generator >>> output on OC0 pin and control register OCR0)

NOTE :
  IN wave generator mode(pwm) :
  Frequency of generator = (Fosc)/(256 * perscaler)
  Duty Cycle (non-inverted) = [(OSR0 + 1)(100)]/256
  Duty Cycle (inverted) = [(255 - OSR0)(100)]/256


*/

#define TIMER0_MODE       TIMER0_NORMAL
//-------------------------------------------------------------

/*
 * Modes used when using wave generator (output on OC0 pin)
 * these modes state what will happen on OC0 pin when the match
 * happens between (OSR0 and TCNT0).
 *
 * you can use this mode 'TIMER0_TOGGLE' in normal mode to generate
 * square wave
 *
 TIMER0_NO_ACTION --->(OC0 works as normal io pin)

 TIMER0_TOGGLE    --->(OC0 TOGGLE whenever match[in non-PWM mode] and )
                  --->(Reserved in PWM mode[don't use it])

 TIMER0_CLEAR     --->(OC0 is CLEARED whenever match[non-inverted])

 TIMER0_SET       --->(OC0 is SET whenever match[inverted])


[non-inverted] >>> the beginning is high
 [inverted] >>> the beginning is low
*/

#define TIMER0_COMPARE_EVENT   TIMER0_NO_ACTION



#endif
