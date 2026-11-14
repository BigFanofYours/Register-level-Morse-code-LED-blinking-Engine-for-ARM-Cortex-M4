#include "nt_ppd_rcc.h"
#include "nt_ppd_rcc_registers.h"

void nt_ppd_RccMcal_ClockInit(void)
{
	volatile uint32_t readBackVal;

	uint32_t sysTickReloadValue = 16000 - 1U; // Assuming a 16 MHz clock for SysTick to generate 1 ms ticks

	// Enable clock
	nt_ppd_RCC_PTR->AHB1ENR |= nt_ppd_RCC_AHB1ENR_GPIOAEN;
	nt_ppd_RCC_PTR->APB2ENR |= nt_ppd_RCC_APB2ENR_USART1EN;

	nt_ppd_SYSTICK_PTR->STK_LOAD = sysTickReloadValue;
	nt_ppd_SYSTICK_PTR->STK_CTRL |= (3UL << 1);
	nt_ppd_SYSTICK_PTR->STK_CTRL |= (1UL << 0);

	// Read back to ensure clock is enabled
	readBackVal = nt_ppd_RCC_PTR->AHB1ENR;
	readBackVal = nt_ppd_RCC_PTR->APB2ENR;
	(void)readBackVal;
}