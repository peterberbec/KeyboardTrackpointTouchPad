#include "KeyboardUSB.h"				/* Initial Github Commit */
#include "ThinkpadKeyboard.h"
#include "MouseUSB.h"
#include "TouchPad.h"
#include "TrackPoint.h"
#include "Globals.h"

void setup()
{
	thinkpadKeyboard.begin();		/* init Thinkpad Keyboard */
	keyboardUSB.begin();			/* init USB keyboard output */
	touchPad.begin();				/* init touchpad mouse input */
	trackPoint.begin();				/* init TrackPoint mouse input */
	mouseUSB.begin();				/* init USB mouse output */
}

void loop()
{	
	thinkpadKeyboard.getData(keyboardData);	/* get data from keyboard */
		keyboardUSB.sendData(keyboardData);	/* send keyboard data over USB */	/* tofix: MAX_KEY_PRESS == 6 */
	touchPad.getData(mouseData);				/* get data from touchPad first, touchPad.getGata is = */
	trackPoint.getData(mouseData);			/* get data from trackPoint second, trackPoint.getData is if(!0) = */
		mouseUSB.sendData(mouseData);			/* send mouse data over USB */
}
