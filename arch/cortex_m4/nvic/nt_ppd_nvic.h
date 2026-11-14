#ifndef nt_ppd_NVIC_H
#define nt_ppd_NVIC_H

#include "nt_ppd_irq.h"

void nt_ppd_NvicMcal_IrqEnable(nt_ppd_Irq_IrqNumT IRQn);
void nt_ppd_NvicMcal_IrqDisable(nt_ppd_Irq_IrqNumT IRQn);

#endif