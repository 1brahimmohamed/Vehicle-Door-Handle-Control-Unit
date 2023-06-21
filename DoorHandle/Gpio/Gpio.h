/**
 * Gpio.h
 *
 *  Created on: Tue Apr 11 2023
 *  Author    : Abdullah Darwish
 */

#ifndef GPIO_H
#define GPIO_H
#include "Std_Types.h"

/*PortName*/
#define GPIO_PORT_A 'A'
#define GPIO_PORT_B 'B'
#define GPIO_PORT_C 'C'
#define GPIO_PORT_D 'D'
#define GPIO_PORT_E 'E'


/*PIN Numbers*/
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15

/*PinMode*/
#define GPIO_INPUT  0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF     0x02
#define GPIO_ANALOG 0x03

/*DefaultState*/

#define GPIO_PUSH_PULL  0x00
#define GPIO_OPEN_DRAIN 0x01

/*Data*/
#define LOW    0x00
#define HIGH   0x01

/*State*/
#define OK 0x01
#define NOK 0x00


#define GPIO_NO_PULL   (0x00 << 1)
#define GPIO_PULL_UP   (0x01 << 1)
#define GPIO_PULL_DOWN (0x02 << 1)

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState);
void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data);
uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum);
uint8 GPIO_ReadPinState(uint8 PortName, uint8 PinNum);

#endif /* GPIO_H */
