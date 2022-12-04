/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 20/3/2022				*/
/*	Version : V01					*/
/************************************/
#include "ADC_config.h"

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


#define ADC1_Base	0x40012400
#define ADC2_Base	0x40012800
#define ADC3_Base	0x40013C00

/******** ADC PRESCALAR ********/
/*
 * Options:
			 CLK_DIVIDE_BY_2	1
			 CLK_DIVIDE_BY_4	2
			 CLK_DIVIDE_BY_6	3
			 CLK_DIVIDE_BY_8	4
 */
#define	CLK_DIVIDE_BY_2			1
#define	CLK_DIVIDE_BY_4			2
#define	CLK_DIVIDE_BY_6			3
#define	CLK_DIVIDE_BY_8			4



/******** ADC CHANNEL SAMPLE RATE ********/

/*
 * Options:
			ADC_CYCLE_1.5
			ADC_CYCLE_7.5
			ADC_CYCLE_13.5
			ADC_CYCLE_28.5
			ADC_CYCLE_41.5
			ADC_CYCLE_55.5
			ADC_CYCLE_71.5
			ADC_CYCLE_239.5
*/

#define ADC_CYCLE_1			1
#define ADC_CYCLE_7			2
#define ADC_CYCLE_13		3
#define ADC_CYCLE_28		4
#define ADC_CYCLE_41		5
#define ADC_CYCLE_55		6
#define ADC_CYCLE_71		7
#define ADC_CYCLE_239		8

typedef struct {
	volatile u32 SR		;
	volatile u32 CR1	;
	volatile u32 CR2	;
	volatile u32 SMPR1  ;
	volatile u32 SMPR2  ;
	volatile u32 JOFR1  ;
	volatile u32 JOFR2  ;
	volatile u32 JOFR3  ;
	volatile u32 JOFR4  ;
	volatile u32 HTR    ;
	volatile u32 LTR    ;
	volatile u32 SQR1   ;
	volatile u32 SQR2   ;
	volatile u32 SQR3   ;
	volatile u32 JSQR   ;
	volatile u32 JDR1   ;
	volatile u32 JDR2   ;
	volatile u32 JDR3   ;
	volatile u32 JDR4   ;
	volatile u32 DR     ;
}ADC_R;

#define ADC1	((volatile ADC_R*)ADC1_Base) // pointer to struct

/*
#define ADC_SR		*((volatile u32*)BaseAddress+0x00)
#define ADC_CR1		*((volatile u32*)BaseAddress+0x04)
#define ADC_CR2		*((volatile u32*)BaseAddress+0x08)
#define ADC_SMPR1   *((volatile u32*)BaseAddress+0x0C)
#define ADC_SMPR2   *((volatile u32*)BaseAddress+0x10)
#define ADC_JOFR1   *((volatile u32*)BaseAddress+0x14)
#define ADC_JOFR2   *((volatile u32*)BaseAddress+0x18)
#define ADC_JOFR3   *((volatile u32*)BaseAddress+0x1C)
#define ADC_JOFR4   *((volatile u32*)BaseAddress+0x20)
#define ADC_HTR     *((volatile u32*)BaseAddress+0x24)
#define ADC_LTR     *((volatile u32*)BaseAddress+0x28)
#define ADC_SQR1    *((volatile u32*)BaseAddress+0x2C)
#define ADC_SQR2    *((volatile u32*)BaseAddress+0x30)
#define ADC_SQR3    *((volatile u32*)BaseAddress+0x34)
#define ADC_JSQR    *((volatile u32*)BaseAddress+0x38)
#define ADC_JDR1    *((volatile u32*)BaseAddress+0x3C)
#define ADC_JDR2    *((volatile u32*)BaseAddress+0x40)
#define ADC_JDR3    *((volatile u32*)BaseAddress+0x44)
#define ADC_JDR4    *((volatile u32*)BaseAddress+0x48)
#define ADC_DR      *((volatile u32*)BaseAddress+0x4C)
*/

#endif
