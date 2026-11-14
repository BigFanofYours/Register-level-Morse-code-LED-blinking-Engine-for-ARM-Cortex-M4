#include "nt_ppd_delay.h"

void nt_ppd_Delay(uint32_t delaySec)
{
	// ~1 second delay
	for (volatile uint32_t i = 0; i < (delaySec * 100000); i++)
	{

	}
};