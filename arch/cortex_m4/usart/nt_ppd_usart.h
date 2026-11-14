#ifndef nt_ppd_USART_H
#define nt_ppd_USART_H

#include <stdint.h>

void nt_ppd_UsartMcal_Usart1Enable(void);
void nt_ppd_UsartMcal_Usart1Init(void);
void nt_ppd_UsartMcal_Usart1SendChar(uint8_t data);
void nt_ppd_UsartMcal_Usart1Transmit(const uint8_t* data);

#endif