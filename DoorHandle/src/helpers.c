/*
 * helpers.c
 *
 *  Created on: May 22, 2023
 *  Author: Ibrahim Mohamed
 */

#include "helpers.h"
#include "Gpio.h"
#include "Gpt.h"


void unlockDoor(enum doorLockingState *doorLockingState){


	if(GPT_GetElapsedTime() > 10 && GPT_GetElapsedTime() < 50){

		/* unlock the door */ 
		*doorLockingState = DOOR_UNLOCKED;

		/*turn on the door lock LED*/
		Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, HIGH);

		/*turn on the ambient light*/
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);

		/*turn on the hazard light*/
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);
	}

	/*hazard light blinking*/
	/*wait for 0.5 sec and turn off hazard light */
	if (GPT_GetElapsedTime() > 550 && GPT_GetElapsedTime() < 1050)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

	/*wait for 0.5 sec and turn on hazard light */
	if (GPT_GetElapsedTime() > 1050 && GPT_GetElapsedTime() < 1550)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);

	/*wait for 0.5 sec and turn off hazard light */
	if(GPT_GetElapsedTime() > 1550 && GPT_GetElapsedTime() < 2050){

		// turn off the ambient light since 2 sec passed
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);

		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

	}

}

void lockDoor(enum doorLockingState *doorLockingState){

	if(GPT_GetElapsedTime() > 10 && GPT_GetElapsedTime() < 50){
		// lock the door
		*doorLockingState = DOOR_LOCKED;

		// turn off the door unlock LED
		Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);

		// turn off the ambient light
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);
		
		// turn on the hazard light
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);
	}
	/*hazard light blinking*/
	/*wait for 0.5 sec and turn off hazard light */

	if (GPT_GetElapsedTime() > 550 && GPT_GetElapsedTime() < 1050)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);
	/*wait for 0.5 sec and turn on hazard light */
	if (GPT_GetElapsedTime() > 1050 && GPT_GetElapsedTime() < 1550)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);

	/*wait for 0.5 sec and turn off hazard light */
	if (GPT_GetElapsedTime() > 1550 && GPT_GetElapsedTime() < 2050)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

}

void openDoor(enum vehicleState *vehicleState)
{
	if(GPT_GetElapsedTime() > 10 && GPT_GetElapsedTime() < 100){
		// open the door
		*vehicleState = OPENED;

		// turn on the ambient light
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);

		// turn off the hazard light (to be clear when interrupting door unlocking)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

	}
}

void closeDoor(enum vehicleState *vehicleState)
{
	if(GPT_GetElapsedTime() > 10 && GPT_GetElapsedTime() < 50){
		// close the door
		*vehicleState = CLOSED;
		// turn off the door unlock LED
		Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);

		// turn off the hazard light LED
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

		// Turn on ambient light
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);
	}

	/*wait for 1 sec and turn off ambient light */
	if(GPT_GetElapsedTime() > 1050 && GPT_GetElapsedTime() < 1150){
		// Turn off ambient light
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);
	}

}

void antiTheft(enum doorLockingState *doorLockingState){

	if(GPT_GetElapsedTime() > 10010 && GPT_GetElapsedTime() < 10550)
	{
		*doorLockingState = DOOR_LOCKED;

		// turn off the door lock LED
		Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);

		// turn off the ambient light
		Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);

		// Turn on hazards light
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);
	}
	/*hazard light blinking 2 times in 2 sec*/
	if (GPT_GetElapsedTime() > 10550 && GPT_GetElapsedTime() < 11050){
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);
	}

	if (GPT_GetElapsedTime() > 11050 && GPT_GetElapsedTime() < 11550)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);


	if (GPT_GetElapsedTime() > 11550 && GPT_GetElapsedTime() < 12050)
		Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

}
