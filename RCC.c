#include "RCC.h"

void RCC_Init(void)
{
	volatile uint32_t temp;
	
	uint32_t SysTick_ReloadValue = 16000 - 1;
	
	// Enable clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	SysTick->STK_LOAD = SysTick_ReloadValue;
	SysTick->STK_CTRL |= (3UL << 1);
	SysTick->STK_CTRL |= (1UL << 0);
	
	// Read back to ensure clock is enabled
	temp = RCC->AHB1ENR;
	temp = RCC->APB2ENR;
	(void)temp;
}