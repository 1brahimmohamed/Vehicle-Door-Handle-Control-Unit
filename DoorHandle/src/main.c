/*
 * main.c
 *
 *  Created on: May 21, 2023
 *  Author: Ibrahim Mohamed
 */

#include "helpers.h"
#include "Rcc.h"
#include"Exti.h"

#include "Gpio.h"
#define LOCK_LED 0
#define AMBIENT_LED 5
#define HAZARD_LED 10

#define LOCK_UNLOCK_BTN 0
#define OPEN_CLOSE_BTN 3

enum doorLockingState doorLockingState;
enum vehicleState vehicleState;



//void EXTI0_IRQHandler(void)
//{
//	//if door is closed and locked -->  unlock
//	Exti_Disable(3);
//	if((doorLockingState == DOOR_LOCKED)&&(vehicleState == CLOSED))
//	{
//		unlockDoor(&doorLockingState);
//	}
//	//if door is closed and unlocked -->  lock
//	else if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
//	{
//		lockDoor(&doorLockingState);
//	}
//	//if door is open  -->  nothing
//	//clear pending flag
//	Clear_Flag(0);
//
//	Exti_Enable(3);
//
//}

//void EXTI3_IRQHandler(void)
//{
//	Exti_Disable(0);
//	//if door is closed and unlocked -->  open
//	if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
//	{
//		openDoor(&vehicleState);
//	}
//	//if door is opened and unlocked -->  close
//
//	else if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == OPENED))
//	{
//		closeDoor(&vehicleState);
//	}
//	//if door is locked  -->  nothing
//
//	//clear pending flag
//	Clear_Flag(3);
//	Exti_Enable(0);
//
//}

int main(void){


	/*enable PORT A and B */
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
//	Rcc_Enable(RCC_SYSCFG); //enable exti and system config
	GPT_Init();


	/*set LED pins as outputs*/
	Gpio_ConfigPin(GPIO_PORT_B, LOCK_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_ConfigPin(GPIO_PORT_B, AMBIENT_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_ConfigPin(GPIO_PORT_B, HAZARD_LED, GPIO_OUTPUT, GPIO_PUSH_PULL);


	/*set push buttons as inputs*/
	Gpio_ConfigPin(GPIO_PORT_A, LOCK_UNLOCK_BTN, GPIO_INPUT, GPIO_PULL_UP);
	Gpio_ConfigPin(GPIO_PORT_A, OPEN_CLOSE_BTN, GPIO_INPUT, GPIO_PULL_UP);

//	Exti_Init( LOCK_UNLOCK_BTN,  EXTI_TRIGGER_FALLING,GPIO_PORT_A);
//	Exti_Init( OPEN_CLOSE_BTN,  EXTI_TRIGGER_FALLING,GPIO_PORT_A);

	/*default state all LEDS are off and door is locked & closed*/
	Gpio_WritePin(GPIO_PORT_B, LOCK_LED, LOW);
	Gpio_WritePin(GPIO_PORT_B, AMBIENT_LED, LOW);
	Gpio_WritePin(GPIO_PORT_B, HAZARD_LED, LOW);

	doorLockingState = DOOR_LOCKED;
	vehicleState = CLOSED;

	GPT_StartTimer(15000);
	while(1)
	{


		//if door is closed and unlocked no btns pressed for more then 10 s-->  lock (antitheft lock)

		if(GPIO_ReadPinState(GPIO_PORT_A, OPEN_CLOSE_BTN)){

			//if door is closed and unlocked -->  open
			if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == OPENED))
			{
				closeDoor(&vehicleState);
			}
			//if door is opened and unlocked -->  close

			else if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
			{
				openDoor(&vehicleState);
				for(int i = 0;i<100000;i++);
			}
			//if door is locked  -->  nothing
			 GPT_StartTimer(15000);

		}

		if(GPIO_ReadPinState(GPIO_PORT_A, LOCK_UNLOCK_BTN)){
			if((doorLockingState == DOOR_LOCKED)&&(vehicleState == CLOSED))
			{
				unlockDoor(&doorLockingState);
			}
			//if door is closed and unlocked -->  lock
			else if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
			{
				lockDoor(&doorLockingState);
			}
			//if door is open  -->  nothing
			 GPT_StartTimer(15000);

		}

		if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
		{
			if (GPT_GetElapsedTime() >= 1000){
			doorLockingState = DOOR_LOCKED;
			// turn on the door unlock LED
			Gpio_WritePin(GPIO_PORT_B, LOCK_LED, LOW);

			// turn on the ambient light
			Gpio_WritePin(GPIO_PORT_B, AMBIENT_LED, LOW);
			// blink the hazard two times lights each time 0.5 high and 0.5 low
			blinkHazardLights();}

		}

	}
	return 0;
}




