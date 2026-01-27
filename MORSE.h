#ifndef MORSE_H
#define MORSE_H

#include <stdint.h>

typedef enum
{
	STATE_LED_ON 			= 0,
	STATE_LED_OFF 		= 1,
	STATE_CHAR_GAP		= 2,
	STATE_WORD_GAP 		= 3,
}State;

typedef struct
{
	uint8_t Morse_Code;
	uint8_t Morse_Length;
}Morse_Typedef;

typedef struct
{
	const Morse_Typedef *Code;
	State Morse_State;
	
	uint32_t Morse_Duration;
	uint32_t Morse_TimeStamp;
	int Morse_SymbolIndex;
	uint8_t Morse_CharAvailable;
}Morse_HandleTypedef;

void Morse_StartChar(char RX_Character); 
void Morse_Update(void);

#endif