/*
 * Gpt.h
 *
 *  Created on: Jun 14, 2023
 *  Author: Ibrahim Mohamed
 */

#ifndef GPT_H_
#define GPT_H_s

#include "Std_Types.h"

#define GPT_PRESCALER 	15999
#define GPT_TIMER 		TIM2

void 	GPT_Init(void);
void 	GPT_StartTimer(uint32 OverFlowTicks);
uint8 	GPT_CheckTimeIsElapsed(void);
uint32 	GPT_GetElapsedTime(void);
uint32 	GPT_GetRemainingTime(void);

#endif /* GPT_H_ */
