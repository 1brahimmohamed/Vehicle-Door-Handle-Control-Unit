/*
 * Exti.h
 *
 *  Created on: May 23, 2023
 *  Author: mahamedhat
 */

#ifndef EXTI_H_
#define EXTI_H_


#include "Bit_Operations.h"
#include "Gpio.h"
#define NVIC_ISER0 (*(uint32 *)0xE000E100)
#define NVIC_ISER1 (*(uint32 *)(0xE000E100 + 0x004))


#define EXTI_TRIGGER_FALLING 0
#define EXTI_TRIGGER_RISING 1
#define EXTI_TRIGGER_RISING_FALLING 2

typedef struct {
	uint32 IMR;
	uint32 EMR;
	uint32 RTSR;
	uint32 FTSR;
	uint32 SWIER;
	uint32 PR;
} ExtiType;

typedef struct {

	uint32 MEMRMP;
	uint32 PMC;
	uint32 EXTICR1; //exti0 to exti3
	uint32 EXTICR2; //exti4 to exti7
	uint32 EXTICR3; //exti8 to exti11
	uint64 EXTICR4; //exti12 to exti15
} SYSCFG_Type;

#define EXTI ((ExtiType *)0x40013C00)
#define SYSCFG ((SYSCFG_Type *)0x40013800)
void Exti_Init(uint8 EXTI_Line, uint8 Trigger_Type,uint8 PortName);
void Exti_Enable(uint8 EXTI_Line);
void Exti_Disable(uint8 EXTI_Line);
void Clear_Flag(uint8 EXTI_Line);



#endif /* EXTI_H_ */
