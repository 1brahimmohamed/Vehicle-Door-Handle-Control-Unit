/*
 * main.c
 *
 *  Created on: May 24, 2023
 *      Author: Maye
 */

#include "Gpio.h"
#include "Rcc.h"
#include "Rcc_Private.h"
#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Gpt.h"

typedef struct
{
   uint32 CR1;    // Control register 1
   uint32 CR2;    // Control register 2
   uint32 SR;     // Status register
   uint32 CNT;    // Counter
   uint32 PSC;    // Prescaler
   uint32 ARR;    // Auto-reload register
} GPT_Type;

int main(){
	// RCC
	Rcc_Init();					// INITIALIZE RCC
	Rcc_Enable(RCC_TIM2);       // ENABLE TIMER2
	Rcc_Enable(RCC_GPIOA);  	// ENABLE GPIO A


	while (1) {
	}

	return 0;
}

// Constants
#define GPT_TICK_DURATION_MS 500

// Create a pointer to Timer 2 registers
#define TIM2 ((GPT_Type *)TIM2_BASE_ADDRESS)

#define TIM2_BASE_ADDRESS 	0x40000000 // Define the base address of Timer 2
#define TIM2_CR1_OFFSET 	0x00
#define TIM2_SR_OFFSET 		0x10
#define TIM_CR1_CEN			(1U << 0) // Enable the timer
#define TIM_SR_UIF			(1U << 0) // Update interrupt flag

// Variables
static unsigned long int gpt_start_ticks;
static unsigned long int gpt_overflow_ticks;
static float gpt_tick_duration;

// Function to initialize the GPT registers
void GPT_Init(void)
{
    // Configure GPT registers
    TIM2->CR1 = 0;          // Clear GPT control register 1

    // Calculate the tick duration based on the microcontroller clock frequency and prescaler value
    uint32 clockFrequency = SystemCoreClock;
    uint32 prescaler = (clockFrequency / 1000) - 1;
    gpt_tick_duration = (1.0f / (float)(clockFrequency / (prescaler + 1))) * 1000.0f;
    TIM2->PSC = prescaler;  // Set the prescaler for 1ms
}

// Function to start the GPT timer
void GPT_StartTimer(unsigned long int OverflowTicks)
{
    // Store the overflow ticks and reset start_ticks
    gpt_overflow_ticks = OverflowTicks;
    gpt_start_ticks = TIM2->CNT;

    // Enable GPT and start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Function to check if an overflow occurred
unsigned char GPT_CheckTimeIsElapsed(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0) {
        TIM2->SR &= ~TIM_SR_UIF;  // Clear the overflow flag
        return 1;                 // Overflow occurred
    }
    return 0;  // No overflow occurred
}

// Function to get the elapsed time since GPT_StartTimer was called
unsigned long int GPT_GetElapsedTime(void)
{
    unsigned long int current_ticks = TIM2->CNT;

    if (current_ticks >= gpt_start_ticks) {
        return (unsigned long int)((current_ticks - gpt_start_ticks) * gpt_tick_duration);
    } else {
        return (unsigned long int)(((0xFFFFFFFF - gpt_start_ticks + 1) + current_ticks) * gpt_tick_duration);
    }
}

// Function to get the remaining time until the overflow ticks passed to GPT_StartTimer
unsigned long int GPT_GetRemainingTime(void)
{
    unsigned long int current_ticks = TIM2->CNT;

    if (current_ticks >= gpt_start_ticks) {
        return (unsigned long int)((gpt_overflow_ticks - (current_ticks - gpt_start_ticks)) * gpt_tick_duration);
    } else {
        return (unsigned long int)((gpt_overflow_ticks - ((0xFFFFFFFF - gpt_start_ticks + 1) + current_ticks)) * gpt_tick_duration);
    }
}
