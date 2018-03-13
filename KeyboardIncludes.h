#ifndef KeyboardIncludes_h
#define KeyboardIncludes_h

/* check out https://github.com/NicoHood/HID */
#ifndef HID_H_PRB
#define HID_H_PRB
#include "HID.h"
#endif

#ifndef MAX_KEY_PRESS
#define MAX_KEY_PRESS		6
#endif

static const uint8_t keyboard_hidReportDescriptor[] PROGMEM = {
0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x85, HID_PROTOCOL_KEYBOARD,  0x05, 0x07, 0x19, 0xE0, 0x29, 0xE7,
0x15, 0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x08, 0x81, 0x02, 0x95, 0x01, 0x75, 0x08, 0x81, 0x03, 0x95,
0x06, 0x75, 0x08, 0x15, 0x00, 0x25, 0x65, 0x05, 0x07, 0x19, 0x00, 0x29, 0x65, 0x81, 0x00, 0xC0 };

typedef struct
{
	uint8_t modifiers;
	uint8_t reserved;
	uint8_t keys[MAX_KEY_PRESS];
} KeyReport;

#ifndef KeyboardDefines
#define KeyboardDefines

#define LAST_PIN			55	/* pin last wire is sent to */

#define TOTAL_INPUT_PINS		17
#define TOTAL_OUTPUT_PINS	10

/* TOFIX: This needs to be higher */
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

#ifndef HID_H_PRB
#define HID_H_PRB
#include "HID.h"
#endif

volatile uint8_t keysCurrentlyPressed[MAX_KEY_PRESS];
volatile uint8_t numKeysCurrentlyPressed;
uint8_t outPin;

/* Determined from hours of trial and error */
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
#endif
