/**
 * Gpio.c
 *
 *  Created on: Tue Apr 11 2023
 *  Author    : Abdullah Darwish
 */

#include "Gpio.h"

#include "Gpio_Private.h"

uint32 GPIO_Addresses[5] = { 0x40020000, 0x40020400 , 0x40020800, 0x40020C00, 0x40021000 };

#define GPIO_REG(REG_ID, PORT_ID) ((uint32*)((PORT_ID) + (REG_ID)))

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,
		uint8 DefaultState) {

	uint8 PortId = PortName - GPIO_PORT_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];

	uint8 OutputState = DefaultState & 0x1;
	uint8 InputState = DefaultState >> 1;

	gpioReg->GPIO_MODER &= ~(0x3 << (2 * PinNum));
	gpioReg->GPIO_MODER |= (PinMode << (2 * PinNum));

	gpioReg->GPIO_OTYPER  &= ~(0x01 << PinNum);
	gpioReg->GPIO_OTYPER |= (OutputState << PinNum);

	gpioReg->GPIO_PUPDR &= ~(0x3 << (2 * PinNum));
	gpioReg->GPIO_PUPDR |= (InputState << (2*PinNum));
}

void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {
	uint8 PortId = PortName - GPIO_PORT_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];
	gpioReg->GPIO_ODR &= ~(0x01 << PinNum);
	gpioReg->GPIO_ODR |= (Data << PinNum);
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum) {
	uint8 data = 0;
	uint8 PortId = PortName - GPIO_PORT_A;
	GpioType * gpioReg =  GPIO_Addresses[PortId];
	data = (gpioReg->GPIO_IDR & (1 << PinNum)) >> PinNum;
	return data;
}

uint8 GPIO_ReadPinState(uint8 PortName, uint8 PinNum)
{
	static uint8 oldState = 1;
	uint8 data1, data2, currentState;
	uint16 i;

	data1 = Gpio_ReadPin(PortName, PinNum);
	for(i = 0; i < 10000; i++);
	data2 = Gpio_ReadPin(PortName, PinNum);

	if (data1 == data2)
		currentState = data1;


	if (currentState == 0 && oldState == 1){
		oldState = currentState;
		return 1;
	}

	oldState = currentState;

	return 0;
}

