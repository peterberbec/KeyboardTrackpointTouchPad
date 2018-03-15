#include "ThinkpadKeyboard.h"		/* Initial Github Commit */
#include "PS2Mouse.h"
#include "Globals.h"

void setup()
{
	thinkpadKeyboard.begin();	/* init Thinkpad Keyboard and USB HID keyboard */
	touchPad.begin();			/* init touchpad mouse input */
	trackPoint.begin();			/* init TrackPoint mouse input and USB HID mouse  */
}

void loop()
{	
	thinkpadKeyboard.getData();		/* get data from keyboard */
	ThinkpadKeyboard::sendData();		/* send keyboard data over USB */	/* tofix: MAX_KEY_PRESS == 6 */
	
	touchPad.getData();				/* get data from touchPad first, touchPad.getGata is = */
	trackPoint.getData();			/* get data from trackPoint second, trackPoint.getData is if(!0) = */
	PS2Mouse::sendData();			/* send mouse data over USB */
}
