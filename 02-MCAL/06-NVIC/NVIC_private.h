/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 14/2/2022				*/
/*	Version : V01					*/
/************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H
/* Base Adress 0xE000E100*/
#define NVIC_ISER0			*((u32*)0xE000E100) //Enable External interrupts from 0 to 31
#define NVIC_ISER1			*((u32*)0xE000E104) //Disable External interrupts from 32 to 63

#define NVIC_ICER0			*((u32*)0xE000E180) //Disable External interrupts from 0 to 31
#define NVIC_ICER1			*((u32*)0xE000E184) //Disable External interrupts from 32 to 63

#define NVIC_ISPR0			*((u32*)0xE000E200) //Enable Pending for interrupts from 0 to 31
#define NVIC_ISPR1			*((u32*)0xE000E204) //Enable Pending for interrupts from 32 to 63

#define NVIC_ICPR0			*((u32*)0xE000E280) //Disable Pending for interrupts from 0 to 31
#define NVIC_ICPR1			*((u32*)0xE000E284) //Disable Pending for interrupts from 32 to 63

#define NVIC_IABR0			*((volatile u32*)0xE000E300) //Read Active bits for interrupts from 0 to 31
#define NVIC_IABR1			*((volatile u32*)0xE000E304) //Read Active bits for interrupts from 32 to 63

#define NVIC_IPR			 ((volatile u8 *)0xE000E100 + 0x300)
#define SCB_AIRCR			*((volatile u32 *)0xE000ED00 + 0x0C)
#endif