/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 14/2/2022				*/
/*	Version : V01					*/
/************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

void MNVIC_voidEnableInterrupt (u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31)
	{
		NVIC_ISER0 = (1 << Copy_u8IntNumber); // Faster as it doesn't have or operation
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32; //to turn it back to zero in this reg
		NVIC_ISER1 = (1 << Copy_u8IntNumber);
	}
	else 
	{
		/* Return Error */
	}
}

void MNVIC_voidDisableInterrupt (u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31)
	{
		NVIC_ICER0 = (1 << Copy_u8IntNumber); // Faster as it doesn't have or operation
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32; //to turn it back to zero in this reg
		NVIC_ICER1 = (1 << Copy_u8IntNumber);
	}
	else 
	{
		/* Return Error */
	}
}

void MNVIC_voidSetPendingFlag (u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31)
	{
		NVIC_ISPR0 = (1 << Copy_u8IntNumber); // Faster as it doesn't have or operation
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32; //to turn it back to zero in this reg
		NVIC_ISPR1 = (1 << Copy_u8IntNumber);
	}
	else 
	{
		/* Return Error */
	}
}

void MNVIC_voidClearPendingFlag (u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31)
	{
		NVIC_ICPR0 = (1 << Copy_u8IntNumber); // Faster as it doesn't have or operation
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32; //to turn it back to zero in this reg
		NVIC_ICPR1 = (1 << Copy_u8IntNumber);
	}
	else 
	{
		/* Return Error */
	}
}

u8 MNVIC_GetActiveFlag(u8 Copy_u8IntNumber)
{
	u8 Local_u8Result;
	if (Copy_u8IntNumber <= 31)
	{
		Local_u8Result = GET_BIT(NVIC_IABR0, Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32; //to turn it back to zero in this reg
		Local_u8Result = GET_BIT(NVIC_IABR1, Copy_u8IntNumber);
	}
	else 
	{
		/* Return Error */
	}
	return Local_u8Result;
}

void MNVIC_VoidSetPriority(s8 Copy_s8INTID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority, u32 Copy_u32GROUP)
{
	/* 0x05FA0400 3 Group & sub priority */
	u8 Local_u8Priority = Copy_u8SubPriority | Copy_u8GroupPriority <<((Copy_u32GROUP - 0x05FA0300) / 256);
		/* Core Peripheral */
		
		/* External Peripheral */
	if(Copy_s8INTID >= 0)
	{
		NVIC_IPR[Copy_s8INTID] = Local_u8Priority << 4; 
	}
	SCB_AIRCR = Copy_u32GROUP;
}