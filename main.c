#include "GPIO.h"
#include "Delay.h"
#include "RCC.h"
#include "USART.h"
#include "NVIC.h"
#include "MORSE.h"

// Definitions

// Global variables
volatile uint8_t RX_BUFFER[256];
const char UART_TX_OK[] = "TX OK\r\n";
const char UART_RX_OK[] = "RX OK\r\n";
volatile uint16_t RX_MainIndex = 0;
volatile uint16_t RX_IRQIndex = 0;
volatile uint8_t RX_SequenceReady = 0;
volatile uint32_t SysTickMs;
Morse_HandleTypedef Morse;

//Function declarations
void RX_DataProcessing(void);
void RX_DataProcessing1(void);

int main(void)
{
	RCC_Init();
	GPIO_LEDInit();
	GPIO_USART1Init();
	USART1_Init();
	USART1_Enable();
	GPIO_ResetPin();
	GPIO_TogglePin();
	while(1)	
	{
		Morse_Update();
		
		if(RX_SequenceReady && (Morse.Morse_CharAvailable == 0))
		{
			NVIC_IRQDisable(USART1_IRQn);
			char RX_Character = RX_BUFFER[RX_MainIndex++];
			
			if(RX_Character >= 'a' && RX_Character <= 'z')
			{
				RX_Character -= 32;
			}
			else if(RX_Character >= '0' && RX_Character <= '9')
			{
				RX_Character += 43;
			}
		
			Morse_StartChar(RX_Character);
			
			if(RX_MainIndex >= RX_IRQIndex)
			{
				Morse.Morse_CharAvailable = 0;
				RX_MainIndex = RX_IRQIndex = 0;
				NVIC_IRQEnable(USART1_IRQn);
			}
		}
	}
}

void RX_DataProcessing(void)
{
	NVIC_IRQDisable(USART1_IRQn);
	for(RX_MainIndex = 0; RX_MainIndex <= RX_IRQIndex; RX_MainIndex++)
	{
		
	}
	NVIC_IRQEnable(USART1_IRQn);
}
