/**
 * Gpio.c
 *
 *  Created on: Tue Apr 11 2023
 *  Author    : Abdullah Darwish
 */

#include "Gpio.h"
#include "Gpio_Private.h"

#include "Utils.h"

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,
		uint8 DefaultState) {
	switch (PortName) {
	case GPIO_PORT_A:
	{
		GPIOA_MODER &= ~(0x03 << (PinNum * 2));
		GPIOA_MODER |= (PinMode << (PinNum * 2));

		switch(PinMode){
		case GPIO_INPUT:
		{
			GPIOA_PUPDR &= ~(0x03 << (PinNum * 2));
			GPIOA_PUPDR |= (DefaultState << (PinNum * 2));
			break;
		}
		case GPIO_OUTPUT:
		{
			GPIOA_OTYPER &= ~(0x01 << PinNum);
			GPIOA_OTYPER |= (DefaultState << PinNum);
			break;
		}
		}
		break;
	}

	case GPIO_PORT_B:
	{
		GPIOB_MODER &= ~(0x03 << (PinNum * 2));
		GPIOB_MODER |= (PinMode << (PinNum * 2));

		switch(PinMode){
		case GPIO_INPUT:
		{
			GPIOB_PUPDR &= ~(0x03 << (PinNum * 2) );
			GPIOB_PUPDR |= (DefaultState << (PinNum * 2));
			break;
		}
		case GPIO_OUTPUT:
		{
			GPIOB_OTYPER &= ~(0x01 << PinNum);
			GPIOB_OTYPER |= (DefaultState << PinNum);
			break;
		}
		}
		break;
	}

	case GPIO_PORT_C:
	{
		GPIOC_MODER &= ~(0x03 << (PinNum * 2));
		GPIOC_MODER |= (PinMode << (PinNum * 2));

		switch(PinMode){
		case GPIO_INPUT:
		{
			GPIOC_PUPDR &= ~(0x03 << (PinNum * 2));
			GPIOC_PUPDR |= (DefaultState << (PinNum * 2));
			break;
		}
		case GPIO_OUTPUT:
		{
			GPIOC_OTYPER &= ~(0x01 << PinNum);
			GPIOC_OTYPER |= (DefaultState << PinNum);
			break;
		}
		}
		break;
	}

	case GPIO_PORT_D:
	{
		GPIOD_MODER &= ~(0x03 << (PinNum * 2));
		GPIOD_MODER |= (PinMode << (PinNum * 2));

		switch(PinMode){
		case GPIO_INPUT:
		{
			GPIOD_PUPDR &= ~(0x03 << (PinNum * 2) );
			GPIOD_PUPDR |= (DefaultState << (PinNum*2));
			break;
		}
		case GPIO_OUTPUT:
		{
			GPIOD_OTYPER &= ~(0x01 << PinNum);
			GPIOD_OTYPER |= (DefaultState << PinNum);
			break;
		}
		}
		break;
	}

	default:
		break;
	}
}

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {

	switch (PortName) {
		case GPIO_PORT_A:
		{
			if((GPIOA_MODER & (0x03 << PinNum * 2)) >> (PinNum * 2)== GPIO_OUTPUT){
				GPIOA_ODR &= ~(0x1 << PinNum);
				GPIOA_ODR |= (Data << PinNum);
				return OK;
			}
			else
				return NOK;

			break;
		}


		case GPIO_PORT_B:
			if((GPIOB_MODER & (0x03 << PinNum * 2)) >> (PinNum * 2)== GPIO_OUTPUT){
						GPIOB_ODR &= ~(0x1 << PinNum);
						GPIOB_ODR |= (Data << PinNum);
						return OK;
					}
					else
						return NOK;
			break;

		case GPIO_PORT_C:
			if((GPIOC_MODER & (0x03 << PinNum * 2)) >> (PinNum * 2)== GPIO_OUTPUT){
						GPIOC_ODR &= ~(0x1 << PinNum);
						GPIOC_ODR |= (Data << PinNum);
						return OK;
					}
					else
						return NOK;
			break;

		case GPIO_PORT_D:
			if((GPIOD_MODER & (0x03 << PinNum * 2)) >> (PinNum * 2)== GPIO_OUTPUT){
						GPIOD_ODR &= ~(0x1 << PinNum);
						GPIOD_ODR |= (Data << PinNum);
						return OK;
					}
					else
						return NOK;
			break;

		default:
			break;
		}

	return NOK;
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum){
	uint8 pinValue;

	switch (PortName) {
		    case GPIO_PORT_A:
		    	pinValue = (GPIOA_IDR & (1 << PinNum)) >> (PinNum);
		    	break;

		    case GPIO_PORT_B:
		    	pinValue = (GPIOB_IDR & (1 << PinNum)) >> (PinNum);
		    	break;

		    case GPIO_PORT_C:
		    	pinValue = (GPIOC_IDR & (1 << PinNum)) >> (PinNum);
		    	break;

		    case GPIO_PORT_D:
		    	pinValue = (GPIOD_IDR & (1 << PinNum)) >> (PinNum);
		    	break;

		    default:
		    	pinValue = 0;
		    	break;
		  }

	return pinValue;
}
