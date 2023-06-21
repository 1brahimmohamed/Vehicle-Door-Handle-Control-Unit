/*
 * Exti.c
 *
 *  Created on: May 23, 2023
 *   Author: maha medhat
 */

#include "Rcc.h"
#include "Exti.h"

void Exti_Init(uint8 EXTI_Line, uint8 Trigger_Type,uint8 PortName){

	SET_BIT(EXTI->IMR, EXTI_Line);  // enable exti line by default
	CLEAR_BIT(EXTI->FTSR, EXTI_Line);  //disable falling edge trigger
	CLEAR_BIT(EXTI->RTSR, EXTI_Line);  //disable rising edge trigger

	switch (Trigger_Type) {
	        case EXTI_TRIGGER_RISING:
	        	SET_BIT(EXTI->RTSR, EXTI_Line); // enable rising edge trigger
	            break;
	        case EXTI_TRIGGER_FALLING:
	        	SET_BIT(EXTI->FTSR, EXTI_Line); // enable falling edge trigger
	            break;
	        case EXTI_TRIGGER_RISING_FALLING:
	        	SET_BIT(EXTI->RTSR, EXTI_Line); // enable rising edge trigger
	        	SET_BIT(EXTI->FTSR, EXTI_Line); // enable falling edge trigger
	            break;
	        default:
	            break;
	    }
	//NVIC selection
	// enable line  on nvic (only for lines 0,1,2,3,4 )
	if((EXTI_Line >= 0 )&& (EXTI_Line <5)){
	SET_BIT(NVIC_ISER0, EXTI_Line + 6); }
	// enable line  on nvic (only for lines 5,6,7,8,9 )
	else if(EXTI_Line > 4 && EXTI_Line <10){
	SET_BIT(NVIC_ISER0, 23); }
	// enable line  on nvic (only for lines 10,11,12,13,14,15 )
	else if(EXTI_Line > 9 && EXTI_Line <16){
	SET_BIT(NVIC_ISER1, 8);  //(40-32)
	}

	//EXTI selection
	uint32 *SYSCFG_REG ;
	//selecting the proper SYSCFG register for the interrupt line
	if(EXTI_Line >= 0 && EXTI_Line < 4){
		SYSCFG_REG = &(SYSCFG->EXTICR1);
	}
	else if(EXTI_Line >= 4 && EXTI_Line <8){
		SYSCFG_REG = &(SYSCFG->EXTICR2);
	}
	else if(EXTI_Line >= 8 && EXTI_Line <12){
		SYSCFG_REG =  &(SYSCFG->EXTICR3);
	}
	else if(EXTI_Line >= 12 && EXTI_Line <16){
		SYSCFG_REG =  &(SYSCFG->EXTICR4);
	}
	// ports selection
	//A--> 0 B-->1 c-->2 D-->3
	switch (PortName) {
	    case GPIO_PORT_A:

	    	*SYSCFG_REG &= ~(0x15 << (4 * (EXTI_Line%4)));
	    	*SYSCFG_REG |= (0x00 << (4 * (EXTI_Line%4)));

	      break;
	    case GPIO_PORT_B:

	    	*SYSCFG_REG &= ~(0x15 << (4 * (EXTI_Line%4)));
	    	*SYSCFG_REG |= (0x01 << (4 * (EXTI_Line%4)));
	      break;
	    case GPIO_PORT_C:
	    	*SYSCFG_REG &= ~(0x15 << (4 * (EXTI_Line%4)));
	    	*SYSCFG_REG |= (0x02 << (4 * (EXTI_Line%4)));

	      break;

	    case GPIO_PORT_D:
	    	*SYSCFG_REG &= ~(0x15 << (4 * (EXTI_Line%4)));
	    	*SYSCFG_REG |= (0x03 << (4 * (EXTI_Line%4)));

	      break;
	    default:
	      break;
	  }

}


void Exti_Enable(uint8 EXTI_Line){

	SET_BIT(EXTI->IMR, EXTI_Line);  // enable this exti line
}


void Exti_Disable(uint8 EXTI_Line){
	CLEAR_BIT(EXTI->IMR, EXTI_Line);  // disable this exti line
}

void Clear_Flag(uint8 EXTI_Line){
	SET_BIT(EXTI->PR, EXTI_Line);
}
