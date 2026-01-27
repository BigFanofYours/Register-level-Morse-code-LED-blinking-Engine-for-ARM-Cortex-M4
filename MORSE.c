#include "MORSE.h"
#include "GPIO.h"

#define DIT_TIME 		400
#define DAH_TIME 		(DIT_TIME * 3)
#define WORD_TIME		(DIT_TIME * 7)

const Morse_Typedef MorseTable[36] = {
		/* A */	{0b01,   	2},
		/* B */	{0b1000, 	4},
		/* C */	{0b1010, 	4},
    /* D */ {0b100,  	3},
    /* E */ {0b0,    	1},
    /* F */ {0b0010, 	4},
    /* G */ {0b110,  	3},
    /* H */ {0b0000, 	4},
    /* I */ {0b00,   	2},
    /* J */ {0b0111, 	4},
    /* K */ {0b101,  	3},
    /* L */ {0b0100, 	4},
    /* M */ {0b11,   	2},
    /* N */ {0b10,   	2},
    /* O */ {0b111,  	3},
    /* P */ {0b0110, 	4},
    /* Q */ {0b1101, 	4},
    /* R */ {0b010,  	3},
    /* S */ {0b000,  	3},
    /* T */ {0b1,    	1},
    /* U */ {0b001,  	3},
    /* V */ {0b0001, 	4},
    /* W */ {0b011,  	3},
    /* X */ {0b1001, 	4},
    /* Y */ {0b1011, 	4},
    /* Z */ {0b1100, 	4},
		/* 0 */ {0b11111,	5},
		/* 1 */ {0b01111,	5},
		/* 2 */ {0b00111,	5},
		/* 3 */ {0b00011,	5},
		/* 4 */ {0b00001,	5},
		/* 5 */ {0b00000, 5},
		/* 6 */ {0b10000, 5},
		/* 7 */ {0b11000, 5},
		/* 8 */ {0b11100, 5},
		/* 9 */ {0b11110, 5}
};

extern Morse_HandleTypedef Morse;
extern volatile uint32_t SysTickMs;

void Morse_StartChar(char RX_Character)
{
  if(Morse.Morse_CharAvailable) return;
	
	Morse.Code = &MorseTable[RX_Character - 'A'];
	Morse.Morse_SymbolIndex = Morse.Code->Morse_Length - 1;
	Morse.Morse_State = STATE_LED_ON;
	Morse.Morse_CharAvailable = 1;
}

void Morse_Update(void)
{
	if(!Morse.Morse_CharAvailable) return;
	
	if(SysTickMs - Morse.Morse_TimeStamp < Morse.Morse_Duration) return;
	
	Morse.Morse_TimeStamp = SysTickMs;
	
	switch(Morse.Morse_State)
	{
		case STATE_LED_ON:
			GPIO_ResetPin();
			if(Morse.Code->Morse_Code & (1 << Morse.Morse_SymbolIndex))
			{
				Morse.Morse_Duration = DAH_TIME;
			}
			else 
			{
				Morse.Morse_Duration = DIT_TIME;
			}
			
			Morse.Morse_State = STATE_LED_OFF;
			
			break;
		
		case STATE_LED_OFF:
			GPIO_WritePin();
			Morse.Morse_SymbolIndex--;
			if(Morse.Morse_SymbolIndex < 0)
			{
				Morse.Morse_Duration = DAH_TIME;
				Morse.Morse_State = STATE_CHAR_GAP;
			}
			else 
			{
				Morse.Morse_Duration = DIT_TIME;
				Morse.Morse_State = STATE_LED_ON;
			}
			break;
		
		case STATE_CHAR_GAP:
			Morse.Morse_CharAvailable = 0;
		
		//case STATE_WORD_GAP:
			
		default:
			Morse.Morse_CharAvailable = 0;
			break;
	}
}