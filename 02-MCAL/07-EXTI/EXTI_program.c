/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 17/2/2022				*/
/*	Version : V01					*/
/************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

static void (*EXTI0_CallBack)(void) = NULL	// defined in private.h
//static void (*EXTI0_CallBack[16])(void) = NULL	// Arry of 16 ptr to func 

void MEXTI_voidinit(void)
{
	#if		EXTI_MODE == RISING
	SET_BIT(EXTI -> RTSR, EXTI_LINE);
	#elif	EXTI_MODE == FALLING
	SET_BIT(EXTI -> FTSR, EXTI_LINE);
	#elif	EXTI_MODE == ON_CHANGE
	SET_BIT(EXTI -> RTSR, EXTI_LINE);
	SET_BIT(EXTI -> FTSR, EXTI_LINE);
	#else #error "Wrong Mode and Line Choice"
	#endif 
	/* Disable Interrupt */
	CLR_BIT(EXTI -> IMR, LINE0);
	CLR_BIT(EXTI -> IMR, LINE1 );
	CLR_BIT(EXTI -> IMR, LINE2 );
	CLR_BIT(EXTI -> IMR, LINE3 );
	CLR_BIT(EXTI -> IMR, LINE4 );
	CLR_BIT(EXTI -> IMR, LINE5 );
	CLR_BIT(EXTI -> IMR, LINE6 );
	CLR_BIT(EXTI -> IMR, LINE7 );
	CLR_BIT(EXTI -> IMR, LINE8 );
	CLR_BIT(EXTI -> IMR, LINE9 );
	CLR_BIT(EXTI -> IMR, LINE10);
	CLR_BIT(EXTI -> IMR, LINE11);
	CLR_BIT(EXTI -> IMR, LINE12);
	CLR_BIT(EXTI -> IMR, LINE13);
	CLR_BIT(EXTI -> IMR, LINE14);
	CLR_BIT(EXTI -> IMR, LINE15);
}

void MEXTI_voidEnableEXTI(u8 Copy_u8Line)
{
	SET_BIT(EXTI -> IMR, Copy_u8Line);
}
void MEXTI_voidDisableEXTI(u8 Copy_u8Line)
{
	CLR_BIT(EXTI -> IMR, Copy_u8Line);
}
void MEXTI_voidSWTrigger(u8 Copy_u8Line)
{
	SET_BIT(EXTI -> SWIER, Copy_u8Line);
}
void MEXTI_voidSetSignalLatch(u8 Copy_u8Line, u8 Copy_u8Mode)
{
	switch(Copy_u8Mode)
	{
		case RISING		:	SET_BIT(EXTI -> RTSR, EXTI_LINE); break;
		case FALLING	:	SET_BIT(EXTI -> FTSR, EXTI_LINE); break;
		case ON_CHANGE	:	SET_BIT(EXTI -> RTSR, EXTI_LINE);
							SET_BIT(EXTI -> FTSR, EXTI_LINE); break;
	}
	SET_BIT(EXTI -> IMR, Copy_u8Line);
}

void MEXTI_voidSetCallBack(void (*Ptr)(void))
{
	EXTI0_CallBack = Ptr;
}

void EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();
	/* Clear Pending Bit */
	SET_BIT(EXTI -> PR,0);
}
