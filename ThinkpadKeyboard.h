#ifndef KeyboardIncludes_h
#include "KeyboardIncludes.h"
#endif

#ifndef KeyboardClass
#define KeyboardClass

class ThinkpadKeyboard
{
	public:
		ThinkpadKeyboard();
		void begin();
		void getData();
		void sendData();
		
	private:
		uint16_t _i, _j; /*looping variables */
		const uint8_t  _inputPins[TOTAL_INPUT_PINS]  = { 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, LAST_PIN /* last needs a rewire */ };
		const uint8_t _outputPins[TOTAL_OUTPUT_PINS] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
		KeyReport keyData;
};

ThinkpadKeyboard::ThinkpadKeyboard() /* constructor - setup pins */
{
	for(_i = 0; _i < TOTAL_OUTPUT_PINS; _i++)	/* set all _outputPins as output and set HIGH */
	{
		pinMode(_outputPins[_i], OUTPUT);
		digitalWrite(_outputPins[_i], HIGH);
	}
	for(_j = 0; _j < TOTAL_INPUT_PINS; _j++)	/* set all _inputPins as INPUT_PULLUP */
	{
		pinMode(_inputPins[_j], INPUT_PULLUP);
	}
	attachInterrupt(_inputPins[0],  pin0falling,  FALLING); /* Interrupt is triggered when we put _outputPin low */
	attachInterrupt(_inputPins[1],  pin1falling,  FALLING); /* For Due, Zero, MKR1000 and 101 boards the interrupt number = pin number. */
	attachInterrupt(_inputPins[2],  pin2falling,  FALLING); /* https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ */
	attachInterrupt(_inputPins[3],  pin3falling,  FALLING);
	attachInterrupt(_inputPins[4],  pin4falling,  FALLING);
	attachInterrupt(_inputPins[5],  pin5falling,  FALLING);
	attachInterrupt(_inputPins[6],  pin6falling,  FALLING);
	attachInterrupt(_inputPins[7],  pin7falling,  FALLING);
	attachInterrupt(_inputPins[8],  pin8falling,  FALLING);
	attachInterrupt(_inputPins[9],  pin9falling,  FALLING);
	attachInterrupt(_inputPins[10], pin10falling, FALLING);
	attachInterrupt(_inputPins[11], pin11falling, FALLING);
	attachInterrupt(_inputPins[12], pin12falling, FALLING);
	attachInterrupt(_inputPins[13], pin13falling, FALLING);
	attachInterrupt(_inputPins[14], pin14falling, FALLING);
	attachInterrupt(_inputPins[15], pin15falling, FALLING);
	attachInterrupt(_inputPins[16], pin16falling, FALLING);
	static HIDSubDescriptor nodeKeyboard(keyboard_hidReportDescriptor, sizeof(keyboard_hidReportDescriptor));
	HID().AppendDescriptor(&nodeKeyboard);
}

void ThinkpadKeyboard::begin() /* setup variables */
{
	for(_i = 0; _i < MAX_KEY_PRESS; _i++)
	{
		keysCurrentlyPressed[_i] = 0;
		keyData.keys[_i] = 0;
	}
	keyData.reserved = 0;
	keyData.modifiers = 0;
	numKeysCurrentlyPressed = 0;
}

void ThinkpadKeyboard::getData()
{
	for(outPin = 0; outPin < TOTAL_OUTPUT_PINS ; outPin++)	/* Light up all pins */
	{
		digitalWrite(_outputPins[outPin], LOW);			/* Interrupt triggered by _inputPins falling */
		digitalWrite(_outputPins[outPin], HIGH);		/* keysCurrentlyPressed[current] set to keyboardMatrixChar[outPin][ISR_call_#] in ISR */
	}
	/* loop through keys in keysCurrentlyPressed and put them into the keyreport
	 * _j cycles through keysCurrentlyPressed, _i cycles through open slots in keyreport.keys
	 * loop _j up to numKeysCurrentlyPressed 	- put that many keys into 
	 * loop _i up to MAX_KEY_PRESS			- this many slots
	  */
	for(_j = 0, _i = 0; (_i < MAX_KEY_PRESS) && (_j < numKeysCurrentlyPressed); _j++) 		/* TOFIX: NKRO */
	{
		switch(keysCurrentlyPressed[_j])
		{
			case KEY_VOL_UP:		keyData.keys[_i++] = 0xE0;
								keyData.keys[_i++] = 0x32;
								break;
			case KEY_VOL_DOWN:		keyData.keys[_i++] = 0xE0;
								keyData.keys[_i++] = 0x02;
								break;
			case KEY_MUTE:			keyData.keys[_i++] = 0xE0;
								keyData.keys[_i++] = 0x23;
			case KEY_BREAK:		keyData.keys[_i++] = 0xE0;
								keyData.keys[_i++] = 0x46;
								break;
			case KEY_PAUSE:		keyData.keys[_i++] = 0xE1;
								keyData.keys[_i++] = 0x1D;
								keyData.keys[_i++] = 0x45;
								keyData.keys[_i++] = 0xE1;
								keyData.keys[_i++] = 0x9D;
								keyData.keys[_i++] = 0xC5;
								break;
								// Above Not Working
			case KEY_POWER:		keyData.keys[_i++] = KEY_LEFT_CTRL;
								keyData.keys[_i++] = KEY_LEFT_ALT;
								keyData.keys[_i++] = KEY_DELETE;
								break;
			case KEY_IBM:			keyData.keys[_i++] = KEY_LEFT_CTRL;
								keyData.keys[_i++] = KEY_LEFT_SHIFT;
								keyData.keys[_i++] = KEY_F10;
								break;
			case KEY_FN:			keyData.keys[_i++] = KEY_LEFT_GUI;
								break;
			case KEY_PAGE_LEFT:		keyData.keys[_i++] = KEY_LEFT_CTRL;
								keyData.keys[_i++] = KEY_LEFT_ARROW;
								break;
			case KEY_PAGE_RIGHT:	keyData.keys[_i++] = KEY_RIGHT_CTRL;
								keyData.keys[_i++] = KEY_RIGHT_ARROW;
								break;
			default:				keyData.keys[_i++] = keysCurrentlyPressed[_j];
								break;
		}
	}
	numKeysCurrentlyPressed=0;
}

void ThinkpadKeyboard::sendData() /* send the keyReport over USB HID */
{
	HID().SendReport(HID_PROTOCOL_KEYBOARD,&keyData,sizeof(keyData));
	begin(); /* clear out all the keys */
}
#endif
