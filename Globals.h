#ifndef Globals_h
#define Globals_h

ThinkpadKeyboard thinkpadKeyboard;			/* Set 'extra' pin in thinkpadKeyboard.h */
KeyboardUSB keyboardUSB;					/* USB keyboard class */

TrackPoint trackPoint(A1, A2, A3);			/* (Clock, Data, Reset) */
TouchPad touchPad(A4, A5);				/* (Clock, Data) */
MouseUSB mouseUSB;						/* USB mouse class */

uint8_t mouseData[4];					/* [0] = buttons, [1] = x, [2] = y, [3] = wheel */
KeyReport keyboardData = { 0, 0, { 0 } };	/* keyboard struct. modifiers, reserved, keys[MAX_KEY_PRESS] */

#endif
