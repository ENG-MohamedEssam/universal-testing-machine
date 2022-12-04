/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 14/2/2022				*/
/*	Version : V01					*/
/************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H
void MNVIC_voidEnableInterrupt (u8 Copy_u8IntNumber);
void MNVIC_voidDisableInterrupt (u8 Copy_u8IntNumber);
void MNVIC_voidSetPendingFlag (u8 Copy_u8IntNumber);
void MNVIC_voidClearPendingFlag (u8 Copy_u8IntNumber);
u8 MNVIC_GetActiveFlag (u8 Copy_u8IntNumber);

#define GROUP3			0x05FA0300	//4 bits for group (IPR) => group
#define GROUP4			0x05FA0400	//3 bits for group and 1 bit  for sub group
#define GROUP5			0x05FA0500	//2 bits for group and 2 bit  for sub group
#define GROUP6			0x05FA0600	//1 bit  for group and 3 bits for sub group
#define GROUP7			0x05FA0700	//0 bits for group and 4 bits for sub group

#endif