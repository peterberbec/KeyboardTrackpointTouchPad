#ifndef Globals_h
#define Globals_h

ThinkpadKeyboard thinkpadKeyboard;			/* USB keyboard included in class now */

PS2Mouse trackPoint(A1, A2, A3);			/* (Clock, Data, Reset) */
PS2Mouse touchPad(A4, A5);				/* (Clock, Data) */

#endif
