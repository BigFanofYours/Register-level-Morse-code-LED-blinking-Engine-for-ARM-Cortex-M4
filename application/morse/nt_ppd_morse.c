#include "nt_ppd_morse.h"
#include "nt_ppd_gpio.h"
#include "nt_ppd_irq.h"
#include "nt_ppd_nvic.h"

#define nt_ppd_MORSE_DIT_TIME  150U
#define nt_ppd_MORSE_DAH_TIME  (nt_ppd_MORSE_DIT_TIME * 3)
#define nt_ppd_MORSE_WORD_TIME (nt_ppd_MORSE_DIT_TIME * 4)

static const nt_ppd_Morse_MorseCodeT MorseTable[37] =
{
	{0b01, 2},	  /* A */
	{0b1000, 4},  /* B */
	{0b1010, 4},  /* C */
	{0b100, 3},	  /* D */
	{0b0, 1},	  /* E */
	{0b0010, 4},  /* F */
	{0b110, 3},	  /* G */
	{0b0000, 4},  /* H */
	{0b00, 2},	  /* I */
	{0b0111, 4},  /* J */
	{0b101, 3},	  /* K */
	{0b0100, 4},  /* L */
	{0b11, 2},	  /* M */
	{0b10, 2},	  /* N */
	{0b111, 3},	  /* O */
	{0b0110, 4},  /* P */
	{0b1101, 4},  /* Q */
	{0b010, 3},	  /* R */
	{0b000, 3},	  /* S */
	{0b1, 1},	  /* T */
	{0b001, 3},	  /* U */
	{0b0001, 4},  /* V */
	{0b011, 3},	  /* W */
	{0b1001, 4},  /* X */
	{0b1011, 4},  /* Y */
	{0b1100, 4},  /* Z */
	{0b11111, 5}, /* 0 */
	{0b01111, 5}, /* 1 */
	{0b00111, 5}, /* 2 */
	{0b00011, 5}, /* 3 */
	{0b00001, 5}, /* 4 */
	{0b00000, 5}, /* 5 */
	{0b10000, 5}, /* 6 */
	{0b11000, 5}, /* 7 */
	{0b11100, 5}, /* 8 */
	{0b11110, 5}, /* 9 */
	{0b0, 1},	  /* ' ' */
};

nt_ppd_Morse_MorseHandleT Morse;
extern volatile uint32_t SysTickMs;

static void nt_ppd_Morse_HandleStateMachine(void);
static void nt_ppd_Morse_HandleMsg(void);
static void nt_ppd_Morse_StartChar(uint8_t RX_Character);

void nt_ppd_App_Morse(void)
{
	nt_ppd_Morse_HandleStateMachine();
	nt_ppd_Morse_HandleMsg();
}

static void nt_ppd_Morse_HandleStateMachine(void)
{
	if (!Morse.morseCharAvailable)
		return;

	if (SysTickMs - Morse.morseTimeStamp < Morse.morseDuration)
		return;

	Morse.morseTimeStamp = SysTickMs;

	switch (Morse.morseState)
	{
	case nt_ppd_MORSE_STATE_LED_ON:
		nt_ppd_GpioMcal_ResetPin();
		if (Morse.morseCode->morseSymbol & (1 << Morse.morseSymbolIndex))
		{
			Morse.morseDuration = nt_ppd_MORSE_DAH_TIME;
		}
		else
		{
			Morse.morseDuration = nt_ppd_MORSE_DIT_TIME;
		}

		Morse.morseState = nt_ppd_MORSE_STATE_LED_OFF;

		break;

	case nt_ppd_MORSE_STATE_LED_OFF:
		nt_ppd_GpioMcal_WritePin();
		Morse.morseSymbolIndex--;
		if (Morse.morseSymbolIndex < 0)
		{
			Morse.morseDuration = nt_ppd_MORSE_DAH_TIME;
			Morse.morseState = nt_ppd_MORSE_STATE_CHAR_GAP;
		}
		else
		{
			Morse.morseDuration = nt_ppd_MORSE_DIT_TIME;
			Morse.morseState = nt_ppd_MORSE_STATE_LED_ON;
		}

		break;

	case nt_ppd_MORSE_STATE_CHAR_GAP:
		Morse.morseCharAvailable = 0;
		break;

	case nt_ppd_MORSE_STATE_WORD_GAP:
		nt_ppd_GpioMcal_WritePin();
		Morse.morseDuration = nt_ppd_MORSE_WORD_TIME;
		Morse.morseCharAvailable = 0;

		break;

	default:
		Morse.morseCharAvailable = 0;

		break;
	}
}

static void nt_ppd_Morse_HandleMsg(void)
{
	if (RX_SequenceReady && (Morse.morseCharAvailable == 0))
	{
		nt_ppd_NvicMcal_IrqDisable(nt_ppd_USART_USART1_IRQn);
		char RX_Character = usartRxBuffer[RX_MainIndex++];

		if (RX_Character >= 'a' && RX_Character <= 'z')
		{
			RX_Character -= 32;
		}
		else if (RX_Character >= '0' && RX_Character <= '9')
		{
			RX_Character += 43;
		}

		nt_ppd_Morse_StartChar(RX_Character);

		if (RX_MainIndex >= RX_IRQIndex)
		{
			Morse.morseCharAvailable = 0;
			RX_MainIndex = RX_IRQIndex = 0;
			nt_ppd_NvicMcal_IrqEnable(nt_ppd_USART_USART1_IRQn);
		}
	}
}

static void nt_ppd_Morse_StartChar(uint8_t RX_Character)
{
	if (Morse.morseCharAvailable)
	{
		return;
	}

	Morse.morseCode = &MorseTable[RX_Character - 'A'];
	Morse.morseSymbolIndex = Morse.morseCode->morseLength - 1;
	Morse.morseState = nt_ppd_MORSE_STATE_LED_ON;

	if ((RX_Character - 'A') == 36)
	{
		Morse.morseState = nt_ppd_MORSE_STATE_WORD_GAP;
	}

	Morse.morseCharAvailable = 1;
}