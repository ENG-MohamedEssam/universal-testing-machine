//*********************************************************************************/
/* Author    : Embedded system Sub team                                          */
/* Version   : V01                                                              */
/* Date      : 14 May 2020                                                     */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"


// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
/******** includes Section **********/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MCAL/RCC_interface.h"
#include "MCAL/DIO_interface.h"
#include "MCAL/USART_interface.h"
#include "MCAL/STK_interface.h"
#include "HAL/HX7111_force_sensor.h"
#include "HAL/STEPPER_HAL.h"
#include "MCAL/ADC_interface.h"
//------------------Macros---------
#define START_M             PIN7               // On or high (Toggle)     GPIOA
#define MOTOR_UP            PIN2               // normal push button      GPIOA
#define MOTOR_DOWN          PIN1               // normal push button      GPIOA
#define START_PROCESS       PIN6               //Toggle                   GPIOA
#define TOGGLE              PIN5               // tension or compression  GPIOA
#define PUMB_UP             PIN1               // pump (port B)
#define PUMB_DWON           PIN2               // pump (port B)
//-----------------------------
#define PISTON_UP      PIN0
#define PISTON_DOWN    PIN10
/*************************************/
//-----------------global variables -------
extern u8 global_u8ReceivedData;
float force;
float DeltaLength;
float Area = 125;   //mm2
float length = 70;   // meter
float Stress;
float Strain;
u8 X_axis[100];
u8 Y_axis[100];
int Gcount=0;
char breakpoint = 0;
char val1=0;
u8 flag=0;
/************************************/


/******************* Functions *********************/
void Fault_fun(void)
{
//	TOG_BIT(flag , 0);
//	MGPIO_VidSetPinValue(GPIOA,PIN10,flag);

}

void adjustmotor_UP()
{
	if(MGPIO_u8GetPinValue ( GPIOA , MOTOR_UP))
	{
		STEPPER_FORWARD(GPIOB, PIN14, GPIOB, PIN15,5000); //range time delay from 50 to 1000
	}

	else
	{
		STEPPER_stop(GPIOB, PIN14, GPIOB, PIN15);
	}
}


void adjustmotor_DOWN()
{

   if(MGPIO_u8GetPinValue ( GPIOA , MOTOR_DOWN))
	{
		STEPPER_REVERSE(GPIOB, PIN14, GPIOB, PIN15,5000);
	}
	else
	{
		STEPPER_stop(GPIOB, PIN14, GPIOB, PIN15);
	}
}


void selnoid_UP(){
 	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, HIGH);
    MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
    MSTK_voidSetBusyWait(300000);// 0.3 sec
 	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
    MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
}
void selnoid_DWON(){
 	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
    MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, HIGH);
    MSTK_voidSetBusyWait(300000);// 0.3 sec
 	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
    MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
}

void switches_int(void)
{

	MGPIO_VidSetPinDirection(GPIOA,START_M,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,MOTOR_UP,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,MOTOR_DOWN,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,START_PROCESS,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,TOGGLE,INPUT_FLOATING);

	MGPIO_VidSetPinDirection(GPIOA,PUMB_UP,INPUT_FLOATING);// NEW: port B
	MGPIO_VidSetPinDirection(GPIOA,PUMB_DWON,INPUT_FLOATING);

	MGPIO_VidSetPinDirection(GPIOA,PISTON_UP,OUTPUT_SPEED_10MHZ_PP); //for  pump Up
	MGPIO_VidSetPinDirection(GPIOB,PISTON_DOWN,OUTPUT_SPEED_10MHZ_PP);//for pump down

}

void Compression ()
{  	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, HIGH);
MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
MSTK_voidSetBusyWait(100);
force = ADC_u16ReadChannelPoll(1);
while(force>10 && MGPIO_u8GetPinValue(GPIOA,TOGGLE))
{

	force = ADC_u16ReadChannelPoll(1);
	DeltaLength = ADC_u16ReadChannelPoll(4);
	Stress  = force / Area;  //stress eqn
	Strain  = DeltaLength / length; // srain eqn
	X_axis[Gcount] = (char) Stress * 10;             //i.e. 1.4*10 = 14
	Y_axis[Gcount] = (char) Strain * 10;
	Gcount++;
}
for(int i=0; i<=Gcount; i++){
	MUSART1_voidTransmit(&X_axis[i],1);
	MUSART1_voidTransmit(&Y_axis[i],1);
}
Gcount =0 ;
breakpoint = 1;
}


void Tension(void)
{
	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, HIGH);
	MSTK_voidSetBusyWait(100);
	force = ADC_u16ReadChannelPoll(1);
	while(force>10 && MGPIO_u8GetPinValue(GPIOA,TOGGLE))
	{

		force = ADC_u16ReadChannelPoll(1);
		DeltaLength = ADC_u16ReadChannelPoll(4);
		Stress  = force / Area;  //stress eqn
		Strain  = DeltaLength / length; // srain eqn
		X_axis[Gcount] = (char) Stress * 10;             //i.e. 1.4*10 = 14
		Y_axis[Gcount] = (char) Strain * 10;
		Gcount++;
	}
	for(int i=0; i<=Gcount; i++){
		MUSART1_voidTransmit(&X_axis[i],1);
		MUSART1_voidTransmit(&Y_axis[i],1);
	}
	Gcount =0 ;
	breakpoint = 1;

}



int main(int argc, char* argv[])
{

	// init preigherals and clocks

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);  // clocks for port A
	RCC_voidEnableClock(RCC_APB2,3);  // clocks for port B
	RCC_voidEnableClock(RCC_APB2,9);  // clocks for ADC1
	RCC_voidEnableClock(RCC_APB2,14); // clocks for UART1
	MSTK_voidInit();
	ADC_VoidInit();
	MUSART1_voidInit();
	//--------------------------------
	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_VidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_VidSetPinDirection(GPIOA,PIN10,OUTPUT_SPEED_2MHZ_PP);
	STEPPER_void_init(GPIOB,PIN14,GPIOB,PIN15);
    switches_int();
	MUSART1_voidSetcallBack(Fault_fun);
	u8 Recive_USART=0;
	while(1)
	{
		if(MGPIO_u8GetPinValue(GPIOA,START_M)){



			if(MGPIO_u8GetPinValue(GPIOA,MOTOR_UP) || global_u8ReceivedData == 1U ){

				adjustmotor_UP();
			}
			else if(MGPIO_u8GetPinValue(GPIOA,MOTOR_DOWN) || global_u8ReceivedData == 2U){

				adjustmotor_DOWN();
			}
			else if(MGPIO_u8GetPinValue(GPIOA,PUMB_UP) || global_u8ReceivedData == 3U){

				selnoid_UP();
			}
			else if(MGPIO_u8GetPinValue(GPIOA,PUMB_DWON) || global_u8ReceivedData == 4U){

				selnoid_DWON();
			}
			else if(MGPIO_u8GetPinValue(GPIOA,TOGGLE) || global_u8ReceivedData == 5U){   //Say compression

				Compression();
			}
			else if(!MGPIO_u8GetPinValue(GPIOA,TOGGLE) || global_u8ReceivedData == 6U){   //Say tension

					Tension();
			}

			else {
                   //Do nothing
			}





		}

	}



}
#pragma GCC diagnostic pop

//
// Recive_USART = MUSART1_u8Receive();
//		switch(Recive_USART){
//		case 1:
//			adjustmotor_UP();    // Move Stepper motor Up
//			break;
//		case 2:
//			adjustmotor_DWON();  // Move Stepper motor Up
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//
//
//
//
//
//	     	}
