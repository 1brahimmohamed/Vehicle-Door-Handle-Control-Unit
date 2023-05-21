/*
 * Gpt.h
 *
 *  Created on: May 21, 2023
 *      Author: I1bra
 */

#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"

void GPT_Init(void);
void GPT_StartTimer(unsigned long int OverFlowTicks);
unsigned char GPT_CheckTimeIsElapsed(void);
unsigned long int GPT_GetElapsedTime(void);
unsigned long int GPT_GetRemainingTime(void);


#endif /* GPT_H_ */
