

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "HX_private.h"
#include "HX_config.h"
#include "HX_interface.h"
#include "DIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"

#define ADD0	7
#define ADSK	6

#define MSTK_voidSetBusyWait	//

extern f32 Val 		;
extern u32 Count    ;
extern u32 Sample   ;

void HX_voidInit(void)
{
	Val = 1;
	Count = 0;
	Sample = 0;

	MGPIO_voidSetPinDirection(GPIOB, ADSK, OUTPUT_SPEED_2MHZ_PP ); //CLK
	MGPIO_voidSetPinDirection(GPIOB, ADD0, OUTPUT_SPEED_2MHZ_PP	); //Data
	MGPIO_voidSetPinValue(GPIOB, ADD0, GPIO_HIGH);
	MGPIO_voidSetPinValue(GPIOB, ADSK, GPIO_LOW );

}

u32 HX_u32ReadCount(void)
{

	MGPIO_voidSetPinDirection(GPIOB, ADSK, OUTPUT_SPEED_2MHZ_PP ); //CLK
	MGPIO_voidSetPinDirection(GPIOB, ADD0, INPUT_FLOATING		); //Data


	while (MGPIO_voidGetPinValue(GPIOB,ADD0));

	for (u8 i = 0; i < 24 ; i++)
	{
		MGPIO_voidSetPinValue(GPIOB, ADSK, GPIO_HIGH);
		MSTK_voidSetBusyWait(300);

		Count = Count << 1;

		MGPIO_voidSetPinValue(GPIOB, ADSK, GPIO_LOW );
		MSTK_voidSetBusyWait(300);

		if (MGPIO_voidGetPinValue(GPIOB, ADD0))
		{
			Count++;
		}
	}

	MGPIO_voidSetPinValue(GPIOB, ADSK, GPIO_HIGH);
	MSTK_voidSetBusyWait(300);

	Count = Count ^ 0x800000;

	MGPIO_voidSetPinValue(GPIOB, ADSK, GPIO_LOW);
	return (Count);
}

void HX_voidCalibrate(void)
{
	MUSART1_voidTransmit("\n",1);
	MUSART1_voidTransmit("Calibrating...",14);
	MUSART1_voidTransmit("\n",1);
	MUSART1_voidTransmit("Please wait...",14);
	MUSART1_voidTransmit("\n",1);
	for (u8 i = 0; i < 100; i++)
	{
		Count = HX_u32ReadCount();
		Sample+=Count;
	}
	Sample/=100;
	MUSART1_voidTransmit("Put 100g weight",15);
	MUSART1_voidTransmit("\n",1);
	Count = 0;
	while (Count < 1000)
	{
		Count = HX_u32ReadCount();
		Count = Sample - Count;
	}
	MUSART1_voidTransmit("Please wait...",14);
	MUSART1_voidTransmit("\n",1);
	MSTK_voidSetBusyWait(2000000);
	for (u8 i = 0; i < 100; i++)
	{
		Count = HX_u32ReadCount();
		Val+=Sample - Count;
	}
	Val = Val / 100.0;
	Val = Val / 100.0;
}

u32 HX_u32ReturnedValue (void)
{
	u32 Local_ReturnVal = 0;
	Count = HX_u32ReadCount();
	Local_ReturnVal = (((Count - Sample)/ Val) - 2 * ((Count-Sample) / Val));
	return Local_ReturnVal;
}
