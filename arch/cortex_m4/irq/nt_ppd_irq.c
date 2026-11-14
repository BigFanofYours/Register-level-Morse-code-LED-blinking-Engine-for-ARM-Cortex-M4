#include "nt_ppd_irq.h"
#include "nt_ppd_usart_registers.h"
#include <stdint.h>

volatile uint8_t usartRxBuffer[256];
volatile uint16_t RX_MainIndex = 0U;
volatile uint16_t RX_IRQIndex = 0U;
volatile uint8_t RX_SequenceReady = 0U;
volatile uint32_t SysTickMs;

void USART1_IRQHandler(void)
{
	if (nt_ppd_USART_USART1_PTR->USART_SR & nt_ppd_IRQ_USART1_RXNE)
	{
		uint8_t data = nt_ppd_USART_USART1_PTR->USART_DR;

		if (RX_IRQIndex <= 255)
		{
			RX_BUFFER[RX_IRQIndex++] = data;

			if ('\n' == data)
			{
				RX_SequenceReady = 1;
			}
		}
	}
}

void SysTick_Handler(void)
{
	SysTickMs++;
}

