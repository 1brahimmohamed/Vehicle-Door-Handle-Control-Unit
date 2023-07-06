/*
 * main.c
 *
 *  Created on: May 21, 2023
 *  Author: Ibrahim Mohamed
 */

#include "helpers.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Gpt.h"


enum doorLockingState doorLockingState;
enum vehicleState vehicleState;

int main(void){


	/* enable PORT A and B */
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);

	GPT_Init();


	/*set LED pins as outputs*/
	Gpio_ConfigPin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_ConfigPin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_ConfigPin(HAZARD_LED_PORT, HAZARD_LED_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);


	/*set push buttons as inputs*/
	Gpio_ConfigPin(GPIO_PORT_A, LOCK_UNLOCK_BTN, GPIO_INPUT, GPIO_PULL_UP);
	Gpio_ConfigPin(GPIO_PORT_A, OPEN_CLOSE_BTN, GPIO_INPUT, GPIO_PULL_UP);


	/*default state all LEDS are off and door is locked & closed*/
	Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);
	Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);
	Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

	/* initial states of the vehicle */
	doorLockingState = DOOR_LOCKED;
	vehicleState = CLOSED;

	/* variable to store code scenarios */
	enum cases scenario;

	while(1)
	{

		/* check if btn is pressed */


		if(GPIO_ReadPinState(GPIO_PORT_A, LOCK_UNLOCK_BTN))
		{

			if( (doorLockingState == DOOR_LOCKED) && (vehicleState == CLOSED) )
			{
				/*unlock the door*/
				scenario = case0;
			}

			else if( (doorLockingState==DOOR_UNLOCKED) && (vehicleState == CLOSED) )
			{
				/*lock the door*/
				scenario = case1;
			}
			/*restart timer as a button is pressed*/
			GPT_StartTimer(13000);

		}

		if(GPIO_ReadPinState(GPIO_PORT_A, OPEN_CLOSE_BTN))
		{
			if( (doorLockingState == DOOR_UNLOCKED) && (vehicleState == OPENED))
			{
				/*close the door*/
				scenario = case2;
			}

			/* if door is opened and unlocked -->  close */
			else if((doorLockingState==DOOR_UNLOCKED)&&(vehicleState == CLOSED))
			{
				/*open the door*/
				scenario = case3;
			}
			/*restart timer as a button is pressed*/
			GPT_StartTimer(13000);
		}



		switch(scenario){
		case case0:
			unlockDoor(&doorLockingState);
			break;
		case case1:
			lockDoor(&doorLockingState);
			break;
		case case2:
			closeDoor(&vehicleState);
			break;
		case case3:
			openDoor(&vehicleState);
			break;
		case case4:
			antiTheft(&doorLockingState);
			break;
		}
		/* no button is pressed */
		if( (doorLockingState==DOOR_UNLOCKED) && (vehicleState == CLOSED) ){
			/*closed and unlocked for 10 sec*/
			if(GPT_GetElapsedTime() > 9900){
				/*antitheft locking*/
				scenario = case4;
			}
		}

	}
	return 0;
}




