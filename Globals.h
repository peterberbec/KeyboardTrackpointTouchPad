#ifndef Globals_h
#define Globals_h

ThinkpadKeyboard thinkpadKeyboard;			/* USB keyboard included in class now */

TrackPoint trackPoint(A1, A2, A3);			/* (Clock, Data, Reset) */
TouchPad touchPad(A4, A5);				/* (Clock, Data) */
MouseUSB mouseUSB;						/* USB mouse class */

#endif
