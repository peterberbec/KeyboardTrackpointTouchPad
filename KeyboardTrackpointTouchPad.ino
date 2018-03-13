#include "ThinkpadKeyboard.h"		/* Initial Github Commit */
#include "MouseUSB.h"
#include "PS2Mouse.h"
#include "Globals.h"

void setup()
{
	thinkpadKeyboard.begin();	/* init Thinkpad Keyboard */
	touchPad.begin();			/* init touchpad mouse input */
	trackPoint.begin();			/* init TrackPoint mouse input */
	mouseUSB.begin();			/* init USB mouse output */
}

void loop()
{	
	thinkpadKeyboard.getData();		/* get data from keyboard */
	thinkpadKeyboard.sendData();		/* send keyboard data over USB */	/* tofix: MAX_KEY_PRESS == 6 */
	
	touchPad.getData();				/* get data from touchPad first, touchPad.getGata is = */
	trackPoint.getData();			/* get data from trackPoint second, trackPoint.getData is if(!0) = */
		mouseUSB.sendData();			/* send mouse data over USB */
}
