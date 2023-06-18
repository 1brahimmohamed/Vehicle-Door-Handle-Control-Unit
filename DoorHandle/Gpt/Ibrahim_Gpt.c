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

	TIM_TypeDef *TIMx = GPT_TIMER; // Declare the TIMx pointer


	// Configure the GPT timer
	TIMx->PSC = GPT_PRESCALER; // Set the prescaler value (0 for no prescaling)
	TIMx->ARR = 0xFFFF; // Set the auto-reload value to the maximum (16-bit timer)

	// Configure the GPT control register
	TIMx->CR1 = 0; // Clear the control register
	TIMx->CR1 |= TIM_CR1_ARPE; // Enable auto-reload preload
	TIMx->CR1 |= TIM_CR1_URS; // Only generate interrupts for counter overflow/underflow
	TIMx->CR1 |= TIM_CR1_CEN; // Enable the GPT timer
}

void GPT_StartTimer(uint32 OverFlowTicks)
{
    TIM_TypeDef *TIMx = GPT_TIMER;

    // Set the number of ticks before timer overflow
    TIMx->ARR = OverFlowTicks;

    // Start the timer
    TIMx->CR1 |= TIM_CR1_CEN;
}

uint8 GPT_CheckTimeIsElapsed(void)
{
    TIM_TypeDef *TIMx = GPT_TIMER;

    // Check if an overflow occurred
    if ((TIMx->SR & TIM_SR_UIF) != 0)
    {
        // Clear the overflow flag
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
        elapsedTicks = TIMx->CNT; // Calculate elapsed ticks
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



