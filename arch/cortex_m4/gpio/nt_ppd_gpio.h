#ifndef nt_ppd_GPIO_H
#define nt_ppd_GPIO_H

#include "nt_ppd_rcc_registers.h"
#include "nt_ppd_gpio_registers.h"

void nt_ppd_GpioMcal_LedInit(void);
void nt_ppd_GpioMcal_Usart1Init(void);
void nt_ppd_GpioMcal_WritePin(void);
void nt_ppd_GpioMcal_ResetPin(void);
void nt_ppd_GpioMcal_TogglePin(void);

#endif