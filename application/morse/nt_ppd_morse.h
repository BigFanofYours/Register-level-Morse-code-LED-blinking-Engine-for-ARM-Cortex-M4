#ifndef nt_ppd_MORSE_H
#define nt_ppd_MORSE_H

#include <stdint.h>

typedef enum
{
	nt_ppd_MORSE_STATE_LED_ON   = 0U,
	nt_ppd_MORSE_STATE_LED_OFF  = 1U,
	nt_ppd_MORSE_STATE_CHAR_GAP = 2U,
	nt_ppd_MORSE_STATE_WORD_GAP = 3U,
} nt_ppd_Morse_MorseStateT;

typedef struct
{
	const uint8_t morseSymbol;
	uint8_t       morseLength;
} nt_ppd_Morse_MorseCodeT;

typedef struct
{
	const nt_ppd_Morse_MorseCodeT* morseCode;
	nt_ppd_Morse_MorseStateT       morseState;
	uint32_t 		     		   morseDuration;
	uint32_t 		     		   morseTimeStamp;
	uint8_t 		     		   morseSymbolIndex;
	uint8_t 			 		   morseCharAvailable;
} nt_ppd_Morse_MorseHandleT;

void nt_ppd_App_Morse(void);

#endif