#include "nt_ppd_nvic.h"
#include "nt_ppd_nvic_registers.h"

void nt_ppd_NvicMcal_IrqEnable(nt_ppd_Irq_IrqNumT IRQn)
{
	nt_ppd_NVIC_PTR->NVIC_ISER[IRQn / 32] |= (1UL << (IRQn % 32));
}

void nt_ppd_NvicMcal_IrqDisable(nt_ppd_Irq_IrqNumT IRQn)
{
	nt_ppd_NVIC_PTR->NVIC_ICER[IRQn / 32] |= (1UL << (IRQn % 32));
}