#ifndef nt_ppd_IRQ_H
#define nt_ppd_IRQ_H

typedef enum
{
	nt_ppd_USART_USART1_IRQn = 37U,
} nt_ppd_Irq_IrqNumT;

#define nt_ppd_IRQ_USART1_RXNE (1UL << 5)

void USART1_IRQHandler(void);
void SysTick_Handler(void);

#endif