
#include "delay.h"
#include "stm32f4xx.h"                  // Device header


volatile uint64_t ms,rms;
void systick_init_ms(uint32_t freq)
	{
	__disable_irq();
	SysTick->LOAD=(freq/1000)-1;
	SysTick->VAL=0;
	SysTick->CTRL=7; //0b00000111;
	NVIC_SetPriority(SysTick_IRQn,7);
	__enable_irq();	
}

uint64_t millis(void)
	{
	__disable_irq();
	rms=ms; //store current ms in rms
	__enable_irq();
	return rms;
	}

void SysTick_Handler(void){
ms++;
}

void delay(uint32_t delay)
	{
	
		uint64_t start=millis();
	do
		{}while(millis()-start!=delay);
	}
