#include "nt_ppd_usart.h"
#include "nt_ppd_usart_registers.h"
#include "nt_ppd_irq.h"
#include "nt_ppd_nvic.h"

void nt_ppd_UsartMcal_Usart1Enable(void)
{
	nt_ppd_USART_USART1_PTR->USART_CR1 |= (1UL << 13U);
}

void nt_ppd_UsartMcal_Usart1Init(void)
{
	// Oversampling, word length, stop bit and baud rate config
	nt_ppd_USART_USART1_PTR->USART_CR1 &= ~((1UL << 12U) | (1UL << 15U));
	nt_ppd_USART_USART1_PTR->USART_CR2 &= ~(3UL << 12U);
	nt_ppd_USART_USART1_PTR->USART_BRR |= 0x683;

	// Enable RXNEIE for RX
	nt_ppd_USART_USART1_PTR->USART_CR1 |= (1UL << 5U);

	// Enable RE and TE bit for RX and TX
	nt_ppd_USART_USART1_PTR->USART_CR1 |= ((1UL << 2U) | (1UL << 3U));

	// Enable interrupt for USART1 RX
	nt_ppd_NvicMcal_IrqEnable(nt_ppd_USART_USART1_IRQn);
}

void nt_ppd_UsartMcal_Usart1SendChar(uint8_t data)
{
	while(!(nt_ppd_USART_USART1_PTR->USART_SR & (1UL << 7)))
	{

	}
	nt_ppd_USART_USART1_PTR->USART_DR = data;
}

void nt_ppd_UsartMcal_Usart1Transmit(const uint8_t* data)
{
	while(*data)
	{
		nt_ppd_UsartMcal_Usart1SendChar(*data);
		data++;
	}
}


