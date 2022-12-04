/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 17/2/2022				*/
/*	Version : V01					*/
/************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* line and Mode */

void MEXTI_voidinit(void);
void MEXTI_voidSetSignaLatch(u8 Copy_u8EXTILine, u8 Copy_u8EXTISenseMode);
void MEXTI_voidEnableEXTI(u8 Copy_u8Line);
void MEXTI_voidDisableEXTI(u8 Copy_u8Line);
void MEXTI_voidSWTrigger(u8 Copy_u8Line);

void MEXTI_voidSetCallBack(void (*Ptr)(void));


#endif