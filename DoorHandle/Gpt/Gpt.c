/*
 * Gpt.c
 *
 *  Created on: Jun 14, 2023
 *  Author: Ibrahim Mohamed
 */

#include "Gpt.h"
#include "stm32f4xx.h"

void GPT_Init(void){

	// Enable the GPT clock
	if(GPT_TIMER == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(GPT_TIMER == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(GPT_TIMER == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	if(GPT_TIMER == TIM5)
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

	// TIMx pointer
	TIM_TypeDef *TIMx = GPT_TIMER;

	// pre-scaler value
	TIMx->PSC = GPT_PRESCALER;

	TIMx->EGR |= 1<<0;
}

void GPT_StartTimer(uint32 OverFlowTicks)
{
    TIM_TypeDef *TIMx = GPT_TIMER;

    // clear counter register
    TIMx->CNT = 0;

    // ticks before timer overflow
    TIMx->ARR = OverFlowTicks;

    // Start timer
    TIMx->CR1 |= TIM_CR1_CEN;
}

uint8 GPT_CheckTimeIsElapsed(void)
{
    TIM_TypeDef *TIMx = GPT_TIMER;

    // Check if we reached th time
    if (TIMx->CNT == TIMx->ARR - 1)
    {
        // Clear overflow flag
        TIMx->SR &= ~TIM_SR_UIF;
        return 1; // Overflow occurred
    }
    else
    {
        return 0; // No overflow occurred
    }
}

uint32 GPT_GetElapsedTime(void)
{
    TIM_TypeDef *TIMx = GPT_TIMER;
    uint32 elapsedTicks = 0;

    // Check if an overflow occurred
    if (GPT_CheckTimeIsElapsed())
    {
        elapsedTicks = 0xFFFFFFFF; // Overflow occurred
    }
    else
    {
        elapsedTicks = TIMx->CNT; // elapsed ticks
    }

    return elapsedTicks;
}

uint32 GPT_GetRemainingTime(void)
{
    TIM_TypeDef *TIMx = GPT_TIMER;
    unsigned long int remainingTicks = 0;

    // Check if an overflow occurred
    if ((TIMx->SR & TIM_SR_UIF) != 0)
    {
        remainingTicks = 0; // Overflow occurred
    }
    else
    {
        remainingTicks = TIMx->ARR - TIMx->CNT; // Calculate remaining ticks
    }

    return remainingTicks;
}




