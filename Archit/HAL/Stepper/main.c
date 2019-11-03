
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "avr/io.h"	
#include "avr/delay.h"

#define Coil_Blue     0
#define Coil_Pink     1
#define Coil_Orange   2
#define Coil_Yellow   3

//each 32 rotation gives 5.625 degree in case full step mode
//each 64 rotation gives 5.625 degree in case half step mode
//you must divide the results from the previous step by the number of 
//the steps in the function (4 in case of full step mode)and
//(8 in case of half step mode)

void Stepper_RotateACW(void);
void Stepper_RotateCW(void);

int main()
{
	/* PORT D as output */
	DDRD = 0xff;
	u8 i;

	while (1)
	{
		/* Rotate clock wise for 1 rotation */
		for (i=0;i<512;i++)
		{
			Stepper_RotateCW();
		}

		/* Rotate anti clock wise for 1 rotation */
		for (i=0;i<512;i++)
		{
			Stepper_RotateACW();
		}


	}

	return 0;
}


void Stepper_RotateCW(void)
{
	SET_BIT(PORTD,Coil_Blue); //1
	CLR_BIT(PORTD,Coil_Pink); //0
	CLR_BIT(PORTD,Coil_Yellow);//0
	CLR_BIT(PORTD,Coil_Orange);//0
	_delay_ms(5);

	CLR_BIT(PORTD,Coil_Blue);
	SET_BIT(PORTD,Coil_Pink);
	CLR_BIT(PORTD,Coil_Yellow);
	CLR_BIT(PORTD,Coil_Orange);
	_delay_ms(5);

	CLR_BIT(PORTD,Coil_Blue);
	CLR_BIT(PORTD,Coil_Pink);
	SET_BIT(PORTD,Coil_Yellow);
	CLR_BIT(PORTD,Coil_Orange);
	_delay_ms(5);

	CLR_BIT(PORTD,Coil_Blue);
	CLR_BIT(PORTD,Coil_Pink);
	CLR_BIT(PORTD,Coil_Yellow);
	SET_BIT(PORTD,Coil_Orange);
	_delay_ms(5);
}

void Stepper_RotateACW(void)
{

	CLR_BIT(PORTD,Coil_Blue);
	CLR_BIT(PORTD,Coil_Pink);
	CLR_BIT(PORTD,Coil_Yellow);
	SET_BIT(PORTD,Coil_Orange);
	_delay_ms(5);

	CLR_BIT(PORTD,Coil_Blue);
	CLR_BIT(PORTD,Coil_Pink);
	SET_BIT(PORTD,Coil_Yellow);
	CLR_BIT(PORTD,Coil_Orange);
	_delay_ms(5);

	CLR_BIT(PORTD,Coil_Blue);
	SET_BIT(PORTD,Coil_Pink);
	CLR_BIT(PORTD,Coil_Yellow);
	CLR_BIT(PORTD,Coil_Orange);
	_delay_ms(5);

	SET_BIT(PORTD,Coil_Blue);
	CLR_BIT(PORTD,Coil_Pink);
	CLR_BIT(PORTD,Coil_Yellow);
	CLR_BIT(PORTD,Coil_Orange);
	_delay_ms(5);
}
