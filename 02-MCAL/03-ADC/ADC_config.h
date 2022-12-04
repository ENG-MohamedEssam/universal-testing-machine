/************************************/
/*	Author  : Mohamed Essam			*/
/*	Date 	: 20/3/2022				*/
/*	Version : V01					*/
/************************************/
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H


/******** ADC PRESCALAR ********/
/*
 * Options:
			 CLK_DIVIDE_BY_2	1
			 CLK_DIVIDE_BY_4	2
			 CLK_DIVIDE_BY_6	3
			 CLK_DIVIDE_BY_8	4
 */
#define ADC_PRESCALAR		CLK_DIVIDE_BY_6

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
#define ADC_SAMPLE_RATE		ADC_CYCLE_239

#endif
