#ifndef _TIMER1_CONFIG_H
#define _TIMER1_CONFIG_H


//-------------------------------------------------------------
/*
 * Modes of the timer/counter1


0-  TIMER1_NORMAL 		        (works as timer or counter)
1-  TIMER1_PHASE_PWM_8BIT       (fixed frequency)
2-  TIMER1_PHASE_PWM_9BIT       (fixed frequency)
3-  TIMER1_PHASE_PWM_10BIT      (fixed frequency)
4-  TIMER1_CTC_OCR1A            (works as timer or counter)
5-  TIMER1_FAST_PWM_8BIT        (fixed frequency)
6-  TIMER1_FAST_PWM_9BIT        (fixed frequency)
7-  TIMER1_FAST_PWM_10BIT       (fixed frequency)
8-  TIMER1_PHASE_FREQUENCT_PWM_ICR1      (Variable frequency)
9-  TIMER1_PHASE_FREQUENCT_PWM_OCR1A     (Variable frequency)
10- TIMER1_PHASE_PWM_ICR1       (Variable frequency)
11- TIMER1_PHASE_PWM_OCR1A      (Variable frequency)
12- TIMER1_CTC_ICR1             (works as timer or counter)
13- no mode
14- TIMER1_FAST_PWM_ICR1        (Variable frequency)
15- TIMER1_FAST_PWM_OCR1A       (output on OC1B only)(Variable frequency)
--------------------------------------------------------------------
Notes About Each Mode :

0- TIMER1_NORMAL
max (65,535), flag TOV1.

1-TIMER1_PHASE_PWM_8BIT        (fixed frequency)
max 255, flag TOV1.

2- TIMER1_PHASE_PWM_9BIT       (fixed frequency)
max 511,  flag TOV1.

3- TIMER1_PHASE_PWM_10BIT      (fixed frequency)
max 1023,  flag TOV1.

4- TIMER1_CTC_OCR1A  (clean timer on compare)(works as timer or counter)
max >> 0xFFFF   ,       top (OCR1B >> 0  ­ 65,535 )
flag >> OCF1B  ,    output on OC1B

5- TIMER1_FAST_PWM_8BIT        (fixed frequency)
max 256, flags((OCF1A / OCF1A) when compare match,
 and TOV1 when TCNT1 overflow)
 output >>( OC1A / OC1B )pins

6- TIMER1_FAST_PWM_9BIT        (fixed frequency)
max 511, flags((OCF1A / OCF1A) when compare match,
 and TOV1 when TCNT1 overflow)
 output >>( OC1A / OC1B )pins

7- TIMER1_FAST_PWM_10BIT       (fixed frequency)
max 1023, flags((OCF1A / OCF1A) when compare match,
 and TOV1 when TCNT1 overflow)
 output >>( OC1A / OC1B )pins

8- TIMER1_PHASE_FREQUENCT_PWM_ICR1      (Variable frequency)
9- TIMER1_PHASE_FREQUENCT_PWM_OCR1A     (Variable frequency)

10- TIMER1_PHASE_PWM_ICR1       (Variable frequency)
max (ICR1 >> 0  ­ 65,535 ), top((OCR1A / OCR1B) >> 0 ­65,535 )
 flags((OCF1A / OCF1B) when compare match,
 and TOV1 when TCNT1 overflow)
 output >>( OC1A / OC1B )pins

11- TIMER1_PHASE_PWM_OCR1A      (Variable frequency)
max (OCR1A >> 0  ­ 65,535 ), top(( OCR1B)only >> 0 ­65,535 )
flags((OCF1B) when compare match, O/P on (OC1B)pin only
 and TOV1 when TCNT1 overflow)

12- TIMER1_CTC_ICR1 (clean timer on compare)(works as timer or counter)
max  >>  65,535 , top((ICR1) >> 0 ­65,535â€¬)
flag ( ICF1) for output compare


13- no mode

14- TIMER1_FAST_PWM_ICR1        (Variable frequency)
max (ICR1 >> 0 -  65,535â€¬), top((OCR1A / OCR1B) >> 0 - 65,535â€¬)
O/P on (OC1A / OC1B), flags (OCF1A / OCF1B)


15- TIMER1_FAST_PWM_OCR1A        (Variable frequency)
max (OCR1A >> 0 - 65,535 ), top((OCR1B) >> 0 ­ 65,535 )
O/P on (OC1B) only, because OCR1A is used for assigning the max
flag (OCF1B)

--------------------------------------------------------------------
General Notes :

(note : [TIMER1_CTC, TIMER1_CTC_OCR1A and TIMER1_CTC_ICR1] can
work as timer or counter it depends on the source of the clock
 >>> input on T1 pin if works as counter)

(note : [ All PWM ] can work as wave generator >>> output on
OC1A / OC1B ..... Except mode15  >>  output on OC1B only

NOTE :
IN wave generator mode(fast-PWM) :=========================

  Frequency of generator = (Fosc) / [(top + 1) * perscaler]

  Duty Cycle (non-inverted) = [(OSRx + 1)(100)]/(top + 1)

  Duty Cycle (inverted) = [(top - OSRx)(100)]/(top + 1)

IN wave generator mode(phase-correct-PWM) :================

  Frequency of generator = (Fosc) / [2 * top * perscaler]

  Duty Cycle (non-inverted) = [( 2 * OSRx )(100)]/(2*top)
                            = [( OSRx )(100)]/(top)

  Duty Cycle (inverted) = [(2*top - 2*OSRx)(100)]/(2*top)
                        = [(top - OSRx)(100)]/(top)


*/

#define TIMER1_MODE       TIMER1_NORMAL
//-------------------------------------------------------------


//-------------------------------------------------------------------
/*
 * Modes used when using wave generator (output on OC0 pin)
 * these modes state what will happen on OC0 pin when the match
 * happens between (OSR0 and TCNT0).
 * you can use this mode 'TIMER0_TOGGLE' in normal mode to generate
 * square wave
 *
 TIMER1_NO_ACTION --->(OC0 works as normal io pin)

 TIMER1_TOGGLE    --->(OC0 TOGGLE whenever match[in non-PWM mode] and )
                  --->(Reserved in PWM mode[don't use it])

 TIMER1_CLEAR     --->(OC1A/OC1B is CLEARED whenever match[non-inverted])

 TIMER1_SET       --->(OC1A/OC1B is SET whenever match[inverted])
 
 
 [non-inverted] >>> the beginning is high
 [inverted] >>> the beginning is low
*/

#define TIMER1_COMPARE1A_EVENT   TIMER1_NO_ACTION
#define TIMER1_COMPARE1B_EVENT   TIMER1_NO_ACTION
//----------------------------------------------------





#endif
