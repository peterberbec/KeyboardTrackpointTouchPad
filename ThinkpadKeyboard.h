#ifndef KeyboardDefines
#define KeyboardDefines

#define LAST_PIN			55	// pin last wire is sent to

#define TOTAL_INPUT_PINS		17
#define TOTAL_OUTPUT_PINS	10

#ifndef MAX_KEY_PRESS
#define MAX_KEY_PRESS		6
#endif

/* Defined by Arduino - don't fuck with these */

#define SHIFT			0x80

#define KEY_LEFT_CTRL	0x80
#define KEY_LEFT_SHIFT	0x81
#define KEY_LEFT_ALT	0x82
#define KEY_LEFT_GUI	0x83
#define KEY_RIGHT_CTRL	0x84
#define KEY_RIGHT_SHIFT	0x85
#define KEY_RIGHT_ALT	0x86
#define KEY_RIGHT_GUI	0x87

#define KEY_UP_ARROW	0xDA
#define KEY_DOWN_ARROW	0xD9
#define KEY_LEFT_ARROW	0xD8
#define KEY_RIGHT_ARROW	0xD7

#define KEY_BACKSPACE	0xB2
#define KEY_TAB		0xB3
#define KEY_RETURN		0xB0
#define KEY_ESC		0xB1
#define KEY_INSERT		0xD1
#define KEY_DELETE		0xD4
#define KEY_PAGE_UP		0xD3
#define KEY_PAGE_DOWN	0xD6
#define KEY_HOME		0xD2
#define KEY_END		0xD5
#define KEY_CAPS_LOCK	0xC1

#define KEY_F1			0xC2
#define KEY_F2			0xC3
#define KEY_F3			0xC4
#define KEY_F4			0xC5
#define KEY_F5			0xC6
#define KEY_F6			0xC7
#define KEY_F7			0xC8
#define KEY_F8			0xC9
#define KEY_F9			0xCA
#define KEY_F10		0xCB
#define KEY_F11		0xCC
#define KEY_F12		0xCD

/* End Defined by Arduino - don't fuck with these */

/* works with custom function press */
#define KEY_PRINT_SCREEN		0x46
#define KEY_INS			0x49
#define KEY_SCROLL_LOCK	 	0x73

/* Don't work 
 look at 	http://www.computer-engineering.org/ps2keyboard/scancodes2.html
		https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html 
		https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2 */
/*					 			press		release */
#define KEY_VOL_UP			0xF6 // 	0xE0, 0x32	0xE0, 0xF0, 0x32
#define KEY_VOL_DOWN		0xF7 // 	0xE0, 0x02	0xE0, 0xF0, 0x21
#define KEY_MUTE			0xF8 // 	0xE0, 0x23	0xE0, 0xF0, 0x23
#define KEY_PAUSE			0xF9 // 	0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5 (No Release)
#define KEY_BREAK			0xFA // 	0xE0, 0x46 	0xC0, 0xC6	KEY_PAUSE + CTRL	

/* remapping */
#define KEY_IBM			0xFB // ctrl + shift + F10 (context menu windows key)
#define KEY_FN				0xFC // windows key
#define KEY_POWER			0xFD // ctrl + alt + del
#define KEY_PAGE_RIGHT		0xFE // ctrl + Right
#define KEY_PAGE_LEFT		0xFF // ctrl + Left

/* ISR Function */
#define setKeyPressed(x) (keysCurrentlyPressed[numKeysCurrentlyPressed++]=keyboardMatrixChar[x][outPin])

#endif

#ifndef KeyboardVariables
#define KeyboardVariables

#include "HID.h"

volatile uint8_t keysCurrentlyPressed[MAX_KEY_PRESS];
volatile uint8_t numKeysCurrentlyPressed;
uint8_t outPin;

const uint8_t keyboardMatrixChar[TOTAL_INPUT_PINS][TOTAL_OUTPUT_PINS] = {
/*		      0		     1		     2		      3			   4		   5				 6			   7			     8		 9 */
/*  0 */ {   '\0',	        'h',	        '6',		    'y',		      'u',	 'j',		    '7',			 'm',		   'n',	    '\0' },
/*  1 */ {   '\0',	     KEY_F6,		   '=',		    ']',		      'i',	 'k',		    '8',			 ',',		  '\0',	    '\0' },
/*  2 */ {   '\0',	     KEY_F5,        KEY_F9,  KEY_BACKSPACE,		     '\0',	'\\',		KEY_F10,	    KEY_RETURN,		   ' ',	    '\0' },
/*  3 */ {   '\0',	       '\0',        KEY_F8,	      KEY_F7,		      'o',	 'l',		    '9',			 '.',		  '\0',	    '\0' },
/*  4 */ {   '\0',	        'g',	        '5',		    't',		      'r',	 'f',		    '4',			 'v',		   'b',	    '\0' },
/*  5 */ {   '\0',	       '\'',	        '-',		    '[',		      'p',	 ';',		    '0',			 'v',		   '/',	    '\0' },
/*  6 */ {   '\0',	     KEY_F4,		KEY_F2,	      KEY_F3,	 	      'e',	 'd',		    '3',			 'c',		  '\0',	    '\0' },
/*  7 */ {   '\0',      KEY_IBM,    KEY_DELETE,   KEY_VOL_DOWN,	    KEY_VOL_UP, KEY_MUTE,		KEY_F11,			'\0',  KEY_DOWN_ARROW,	    '\0' },
/*  8 */ {   '\0',	       '\0',        KEY_F1,  KEY_CAPS_LOCK,		      'w',	 's',		    '2',			 'x',		  '\0',	    '\0' },
/*  9 */ {   '\0',	       '\0',	    KEY_INS,	        '\0',		     '\0',	'\0',		KEY_F12,			'\0', KEY_RIGHT_ARROW,	    '\0' },
/* 10 */ {   '\0',      KEY_ESC,		   '`',	     KEY_TAB, 		      'q',	 'a',		    '1',			 'z',		  '\0',	    '\0' },
/* 11 */ {   '\0',	       '\0',	KEY_PAGE_UP,	        '\0',		     '\0',	'\0',    KEY_PAGE_DOWN,	 KEY_PAGE_LEFT,  KEY_PAGE_RIGHT,	    '\0' },
/* 12 */ {   '\0',	       '\0',		  '\0', KEY_LEFT_SHIFT,		     '\0',	'\0',		   '\0', KEY_RIGHT_SHIFT,		  '\0',	    '\0' },
/* 13 */ {   '\0', KEY_UP_ARROW,      KEY_HOME,	        '\0',		     '\0',	'\0',		KEY_END,		KEY_PAUSE,  KEY_LEFT_ARROW,	    '\0' },
/* 14 */ {   '\0',	       '\0', KEY_LEFT_CTRL,		   '\0',		     '\0',	'\0',		   '\0',	KEY_RIGHT_CTRL,		  '\0',	    '\0' },
/* 15 */ {   '\0', KEY_LEFT_ALT,		  '\0',		   '\0', KEY_SCROLL_LOCK,	'\0', KEY_PRINT_SCREEN,			'\0',   KEY_RIGHT_ALT,	    '\0' },
/* 16 */ { KEY_FN, 	       '\0',		  '\0',		   '\0',		     '\0',	'\0',		   '\0',			'\0',		  '\0', KEY_POWER} };

#endif

#ifndef InterruptServiceRoutines
#define InterruptServiceRoutines

void pin0falling()
{
	setKeyPressed(0);
}
void pin1falling()
{
	setKeyPressed(1);
}
void pin2falling()
{
	setKeyPressed(2);
}
void pin3falling()
{
	setKeyPressed(3);
}
void pin4falling()
{
	setKeyPressed(4);
}
void pin5falling()
{
	setKeyPressed(5);
}
void pin6falling()
{
	setKeyPressed(6);
}
void pin7falling()
{
	setKeyPressed(7);
}
void pin8falling()
{
	setKeyPressed(8);
}
void pin9falling()
{
	setKeyPressed(9);
}
void pin10falling()
{
	setKeyPressed(10);
}
void pin11falling()
{
	setKeyPressed(11);
}
void pin12falling()
{
	setKeyPressed(12);
}
void pin13falling()
{
	setKeyPressed(13);
}
void pin14falling()
{
	setKeyPressed(14);
}
void pin15falling()
{
	setKeyPressed(15);
}
void pin16falling()
{
	setKeyPressed(16);
}

#endif

#ifndef KeyboardClass
#define KeyboardClass

class ThinkpadKeyboard
{
	public:
		ThinkpadKeyboard();
		void begin();
		void getData(KeyReport);
		
	private:
		uint16_t _i, _j; // looping variable
		const uint8_t  _inputPins[TOTAL_INPUT_PINS]  = { 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, LAST_PIN /* last needs a rewire */ };
		const uint8_t _outputPins[TOTAL_OUTPUT_PINS] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
};

ThinkpadKeyboard::ThinkpadKeyboard() // constructor
{
	for(_i = 0; _i < MAX_KEY_PRESS; _i++)
	{
		keysCurrentlyPressed[_i] = 0;
	}
	numKeysCurrentlyPressed = 0;
}

void ThinkpadKeyboard::begin() // setup pins
{
	for(_i = 0; _i < TOTAL_OUTPUT_PINS; _i++)	// set all _outputPins as output and set HIGH
	{
		pinMode(_outputPins[_i], OUTPUT);
		digitalWrite(_outputPins[_i], HIGH);
	}
	for(_j = 0; _j < TOTAL_INPUT_PINS; _j++)	// set all _inputPins as INPUT_PULLUP
	{
		pinMode(_inputPins[_j], INPUT_PULLUP);
	}
	
	attachInterrupt(_inputPins[0],  pin0falling,  FALLING); // For Due, Zero, MKR1000 and 101 boards the interrupt number = pin number.
	attachInterrupt(_inputPins[1],  pin1falling,  FALLING); // https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
	attachInterrupt(_inputPins[2],  pin2falling,  FALLING);
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
}

void ThinkpadKeyboard::getData(KeyReport data)
{
	for(outPin = 0; outPin < TOTAL_OUTPUT_PINS ; outPin++)	/* Light up all pins */
	{
		digitalWrite(_outputPins[outPin], LOW);			/* Interrupt triggered by inPin falling */
		digitalWrite(_outputPins[outPin], HIGH);
	}
	/* loop through keys in keysCurrentlyPressed and put them into the keyreport
	 * _j cycles through keysCurrentlyPressed, _i cycles through open slots in keyreport.keys */
	for(_j = 0, _i = 0; _i < MAX_KEY_PRESS, _j < numKeysCurrentlyPressed; _j++) 		/* TOFIX: NKRO */
	{
		switch(keysCurrentlyPressed[_j])
		{
			case KEY_VOL_UP:		data.keys[_i++] = 0xE0;
								data.keys[_i++] = 0x32;
								break;
			case KEY_VOL_DOWN:		data.keys[_i++] = 0xE0;
								data.keys[_i++] = 0x02;
								break;
			case KEY_MUTE:			data.keys[_i++] = 0xE0;
								data.keys[_i++] = 0x23;
			case KEY_BREAK:		data.keys[_i++] = 0xE0;
								data.keys[_i++] = 0x46;
								break;
			case KEY_PAUSE:		data.keys[_i++] = 0xE1;
								data.keys[_i++] = 0x1D;
								data.keys[_i++] = 0x45;
								data.keys[_i++] = 0xE1;
								data.keys[_i++] = 0x9D;
								data.keys[_i++] = 0xC5;
								break;
								// Above Not Working
			case KEY_POWER:		data.keys[_i++] = KEY_LEFT_CTRL;
								data.keys[_i++] = KEY_LEFT_ALT;
								data.keys[_i++] = KEY_DELETE;
								break;
			case KEY_IBM:			data.keys[_i++] = KEY_LEFT_CTRL;
								data.keys[_i++] = KEY_LEFT_SHIFT;
								data.keys[_i++] = KEY_F10;
								break;
			case KEY_FN:			data.keys[_i++] = KEY_LEFT_GUI;
								break;
			case KEY_PAGE_LEFT:		data.keys[_i++] = KEY_LEFT_CTRL;
								data.keys[_i++] = KEY_LEFT_ARROW;
								break;
			case KEY_PAGE_RIGHT:	data.keys[_i++] = KEY_RIGHT_CTRL;
								data.keys[_i++] = KEY_RIGHT_ARROW;
								break;
			default:				data.keys[_i++] = keysCurrentlyPressed[_j];
								break;
		}
		keysCurrentlyPressed[_j] = 0x00; /* It's been moved into keys for HID report, so clear it in the ISR array */
	}
	while(_i < MAX_KEY_PRESS) /* clear remaining key before sending the HID report. Empties out any keys pressed previously beyond the number pressed this loop */
	{
		data.keys[_i++] = 0x00;
	}
	while(_j < MAX_KEY_PRESS) /* complete the blanking of pressed keys array. This should never happen. */
	{
		keysCurrentlyPressed[_j] = 0x00;
	}
	numKeysCurrentlyPressed=0;
}
#endif
