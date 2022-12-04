
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

#include "RCC_private.h"
#include "DIO_private.h"
#include "NVIC_interface.h"
#include "systick_time.h"



void ADC_VoidInit(void)
{
	//RCC Clock for ADC1 and Altern. Func.
	SET_BIT(RCC_APB2ENR,0); // Enable AFIO
	SET_BIT(RCC_APB2ENR,2); // Enable I/O Port A
	SET_BIT(RCC_APB2ENR,9); // Enable ADC1

	/* Enable ADC Single Contineous mode*/
	SET_BIT(ADC1 -> CR2,0);
	SET_BIT(ADC1 -> CR2,1);
	DelayMs(1);

	/************ Choose Prescalar ************/
#if ADC_PRESCALAR == CLK_DIVIDE_BY_2
	CLR_BIT(RCC_CFGR,14);
	CLR_BIT(RCC_CFGR,15);
#elif ADC_PRESCALAR == CLK_DIVIDE_BY_4
	SET_BIT(RCC_CFGR,14);
	CLR_BIT(RCC_CFGR,15);

#elif ADC_PRESCALAR == CLK_DIVIDE_BY_6
	CLR_BIT(RCC_CFGR,14);
	SET_BIT(RCC_CFGR,15);
#else
	SET_BIT(RCC_CFGR,14);
	SET_BIT(RCC_CFGR,15);
#endif


#if ADC_SAMPLE_RATE == ADC_CYCLE_1
	ADC1 -> SMPR2 = 0x00000000;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_7
	ADC1 -> SMPR2 = 0x09249249;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_13
	ADC1 -> SMPR2 = 0x12492492;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_28
	ADC1 -> SMPR2 = 0x1B6DB6DB;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_41
	ADC1 -> SMPR2 = 0x24924924;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_55
	ADC1 -> SMPR2 = 0x2DB6DB6D;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_71
	ADC1 -> SMPR2 = 0x36DB6DB6;

#elif ADC_SAMPLE_RATE == ADC_CYCLE_239
	ADC1 -> SMPR2 = 0x3FFFFFFF;
#endif

	//Enable ADC for the first Time
	SET_BIT(ADC1 -> CR2,0); // SET ADON bit
	SET_BIT(ADC1 -> CR2,1); // use ADC in continuous Mode
	DelayMs(1); //  1m sec delay

	//Turn ADC on for the second Time
	SET_BIT(ADC1 -> CR2,0); // set ADON bit
	SET_BIT(ADC1 -> CR2,1);
	DelayMs(1); // 1 ms delay

	// Set calibration Bit
	SET_BIT(ADC1 -> CR2,2);
	DelayMs(2); //2 ms delay


}

u16 ADC_u16ReadChannelPoll(u16 Channel_u16Number)/* Channel Num from 0 to 9*/
{
	switch(Channel_u16Number)
	{
	case 0:
		// Analog Mode
		CLR_BIT(GPIOA_CRL,0);
		CLR_BIT(GPIOA_CRL,1);
		CLR_BIT(GPIOA_CRL,2);
		CLR_BIT(GPIOA_CRL,3);
		DelayMs(1);

		//Set the channel  for conversion 	( Channel 0 )
		CLR_BIT(ADC1 -> SQR3,0);
		CLR_BIT(ADC1 -> SQR3,1);
		CLR_BIT(ADC1 -> SQR3,2);
		CLR_BIT(ADC1 -> SQR3,3);
		while((ADC1 -> SR &(1<<1)) == 0);
		break;
	case 1:
		// Analog Mode
		CLR_BIT(GPIOA_CRL,4);
		CLR_BIT(GPIOA_CRL,5);
		CLR_BIT(GPIOA_CRL,6);
		CLR_BIT(GPIOA_CRL,7);
		DelayMs(1);

		//Set the channel  for conversion 	( Channel 1 )
		SET_BIT(ADC1 -> SQR3,0);
		CLR_BIT(ADC1 -> SQR3,1);
		CLR_BIT(ADC1 -> SQR3,2);
		CLR_BIT(ADC1 -> SQR3,3);
		while((ADC1 -> SR &(1<<1)) == 0);
		break;
	}
	return ADC1 -> DR;
}
/*
void ADC1_2_IRQHandler(void)
{
	u32 VAL = 0;
	// Check if the code reached here bec. end of conversion flag is set
	// End of conversion flag is cleared by reading the data register
	while(GET_BIT(ADC_SR,1) == 0);
	return VAL;
	if(ADC_u8CallBackPtr != NULL)
	{
		(*ADC_u8CallBackPtr)();
			MNVIC_voidDisableInterrupt(18);
	}
}

void ADC_voidSetCallBack(void(*ADC_u8Ptr)(void))
{
	ADC_u8CallBackPtr = ADC_u8Ptr;
}

u32 ADC_u32ReturnValue(void)
{
	return ADC1 -> DR;
}
*/
