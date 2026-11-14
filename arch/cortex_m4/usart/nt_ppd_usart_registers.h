#ifndef nt_ppd_USART_REGISTERS_H
#define nt_ppd_USART_REGISTERS_H

#include <stdint.h>

typedef struct
{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
} nt_ppd_Usart_RegistersT;

#define nt_ppd_USART_USART1_BASE_ADDR (0x40011000UL)

#define nt_ppd_USART_USART1_PTR       ((nt_ppd_Usart_RegistersT*) nt_ppd_USART_USART1_BASE_ADDR)

#endif