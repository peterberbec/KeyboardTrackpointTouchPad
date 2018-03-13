#ifndef Globals_h
#define Globals_h

ThinkpadKeyboard thinkpadKeyboard;		/* Set 'extra' pin in thinkpadKeyboard.h */
KeyboardUSB keyboardUSB;				/* USB keyboard class */

TrackPoint trackPoint(A1, A2, A3);		/* (Clock, Data, Reset) */
TouchPad touchPad(A4, A5);			/* (Clock, Data) */
MouseUSB mouseUSB;					/* USB mouse class */

uint8_t mouseData[4];
KeyReport keyboardData = { 0, 0, { 0 } };

#endif
