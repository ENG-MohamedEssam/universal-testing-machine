
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
void (*CallBack)(void);
volatile u8 global_u8ReceivedData=0;
void MUSART1_voidInit(void)
{
	/*	baud rate = 9600		*/
	USART1 -> BRR = 0x341;

	SET_BIT((USART1-> CR[0]), 3);			/* Enabling Transmitter */
	SET_BIT((USART1-> CR[0]), 2);			/* Enabling Receiver */
	SET_BIT((USART1-> CR[0]), 13);			/* Enabling USART */
	SET_BIT( USART1 -> CR[0] , 5 );         /*Enable interrupt */
	SET_BIT(NVIC_ISER1,5);                  /*NCIV*/
	USART1 -> SR = 0;						/* Clearing status register */
}

void MUSART1_voidTransmit(u8 *arr, u8 length)
{
	u8 i = 0;
	while( length != 0){
		USART1 -> DR = arr[i];
		while((GET_BIT((USART1 -> SR), 6)) == 0);
		i++;
		length--;
	}
	
}

u8 MUSART1_u8Receive(void)
{
	u8 Loc_u8ReceivedData = 0;
	while((GET_BIT((USART1 -> SR), 5)) == 0);
	Loc_u8ReceivedData = USART1 -> DR;
	return (Loc_u8ReceivedData);
}

// NO blocking
u8 MUSART1_u8ReceiveNOinterrupt(void)
{
	u8 Loc_u8ReceivedData = 0;
	Loc_u8ReceivedData = USART1 -> DR;
	return (Loc_u8ReceivedData);
	
}


void MUSART1_voidSetcallBack(void (*setFunPtr)(void)){

	CallBack = setFunPtr;
}
void USART1_IRQHandler(void)
{
	if(GET_BIT((USART1 -> SR), 5)){

         CallBack();
         global_u8ReceivedData =  USART1 -> DR;
         CLR_BIT(USART1 -> SR, 5);
	}

}
















