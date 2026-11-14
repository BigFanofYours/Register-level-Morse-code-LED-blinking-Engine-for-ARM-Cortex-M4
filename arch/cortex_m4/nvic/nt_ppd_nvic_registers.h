#ifndef nt_ppd_NVIC_REGISTERS_H
#define nt_ppd_NVIC_REGISTERS_H

#include <stdint.h>

typedef struct
{
	volatile uint32_t NVIC_ISER[3];
	volatile uint32_t NVIC_ICER[3];
	volatile uint32_t NVIC_ISPR[3];
	volatile uint32_t NVIC_ICPR[3];
	volatile uint32_t NVIC_IABR[3];
	volatile uint32_t NVIC_IPR[3];
	volatile uint32_t STIR;
} nt_ppd_Nvic_RegistersT;

#define nt_ppd_NVIC_BASE_ADDR (0xE000E100UL)

#define nt_ppd_NVIC_PTR 	  ((nt_ppd_Nvic_RegistersT*) nt_ppd_NVIC_BASE_ADDR)

#endif