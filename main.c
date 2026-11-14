#include "nt_ppd_gpio.h"
#include "nt_ppd_delay.h"
#include "nt_ppd_irq.h"
#include "nt_ppd_usart.h"
#include "nt_ppd_nvic.h"
#include "nt_ppd_morse.h"
#include "nt_ppd_rcc.h"
#include "main.h"

// Function declarations
static void nt_ppd_PeripheralInit(void);

int main(void)
{
	nt_ppd_PeripheralInit();

	while (1)
	{
		nt_ppd_App_Morse();
	}
}

static void nt_ppd_PeripheralInit(void)
{
	nt_ppd_RccMcal_ClockInit();
	nt_ppd_GpioMcal_LedInit();
	nt_ppd_GpioMcal_Usart1Init();
	nt_ppd_UsartMcal_Usart1Init();
	nt_ppd_UsartMcal_Usart1Enable();
	nt_ppd_GpioMcal_ResetPin();
	nt_ppd_GpioMcal_TogglePin();
}
