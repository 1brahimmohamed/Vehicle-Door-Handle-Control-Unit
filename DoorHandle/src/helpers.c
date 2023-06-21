/*
 * helpers.c
 *
 *  Created on: May 22, 2023
 *  Author: Ibrahim Mohamed
 */

#include "helpers.h"
#include "Gpio.h"
#include "Gpt.h"

/* LED PORTS */
#define DOOR_LOCK_LED_PORT      GPIO_PORT_B
#define DOOR_UNLOCK_LED_PORT    GPIO_PORT_B
#define HAZARD_LED_PORT         GPIO_PORT_B
#define AMBIENT_LIGHT_LED_PORT  GPIO_PORT_B

/* LED PINS */
#define DOOR_LOCK_LED_PIN       GPIO_PIN_0
#define HAZARD_LED_PIN          GPIO_PIN_1
#define AMBIENT_LIGHT_LED_PIN   GPIO_PIN_2

/* TIME VALUES in millisecond */
#define BLINK_DELAY_TICKS    500
#define AMBIENT_LIGHT_DELAY_TICKS 2000

void unlockDoor(enum doorLockingState *doorLockingState){
    // lock the door
    *doorLockingState = DOOR_UNLOCKED;

    // turn on the door unlock LED
    Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, HIGH);


    // turn on the ambient light
    Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);

    // blink the hazard two times lights each time 0.5 high and 0.5 low
    blinkHazardLights();

    // turn off the ambient light
    Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);
}

void lockDoor(enum doorLockingState *doorLockingState){
    // lock the door
    *doorLockingState = DOOR_LOCKED;

    // turn off the door unlock LED
    Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);

    // turn off the ambient light
    Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);

    // blink the hazard two times lights each time 0.5 high and 0.5 low
    blinkHazardLights();
}

void openDoor(enum vehicleState *vehicleState)
{

	// open the door
	*vehicleState = OPENED;

    // turn on the ambient light
    Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);

}


void closeDoor(enum vehicleState *vehicleState)
{
	// close the door
	*vehicleState = CLOSED;
	// turn off the door unlock LED
	Gpio_WritePin(DOOR_LOCK_LED_PORT, DOOR_LOCK_LED_PIN, LOW);

	// turn off the hazard light LED
	Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

    // Turn on ambient light
	Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, HIGH);

    // Wait for the GPT timer

    GPT_StartTimer(AMBIENT_LIGHT_DELAY_TICKS);
    while (!GPT_CheckTimeIsElapsed());

    // Turn off ambient light
    Gpio_WritePin(AMBIENT_LIGHT_LED_PORT, AMBIENT_LIGHT_LED_PIN, LOW);

}


void blinkHazardLights(void){
    uint8 i;
    for (i = 0; i < 2; i++)
    {
        // Turn on hazard LED
    	Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, HIGH);

        // Wait for the GPT timer

        GPT_StartTimer(BLINK_DELAY_TICKS);
        while (!GPT_CheckTimeIsElapsed());

        // Turn off hazard LED
        Gpio_WritePin(HAZARD_LED_PORT, HAZARD_LED_PIN, LOW);

        // Wait for the GPT timer
        GPT_StartTimer(BLINK_DELAY_TICKS);
        while (!GPT_CheckTimeIsElapsed());
    }
}
