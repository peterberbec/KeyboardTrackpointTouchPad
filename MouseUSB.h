#ifndef mouseUSB_h
#define mouseUSB_h

#ifndef HID_H_PRB
#define HID_H_PRB
#include "HID.h"
#endif

static const uint8_t mouse_hidReportDescriptor[] PROGMEM = { 0x05, 0x01, 0x09, 0x02, 0xa1, 0x01, 0x09,
	  0x01, 0xa1, 0x00, 0x85, 0x01, 0x05, 0x09, 0x19, 0x01, 0x29, 0x03, 0x15, 0x00, 0x25, 0x01, 0x95,
	  0x03, 0x75, 0x01, 0x81, 0x02, 0x95, 0x01, 0x75, 0x05, 0x81, 0x03, 0x05, 0x01, 0x09, 0x30, 0x09,
	  0x31, 0x09, 0x38, 0x15, 0x81, 0x25, 0x7f, 0x75, 0x08, 0x95, 0x03, 0x81, 0x06, 0xc0, 0xc0 };

class MouseUSB
{
	public:
		MouseUSB();
		void begin();
		void sendData(uint8_t[4]);
};

MouseUSB::MouseUSB()
{
}

void MouseUSB::begin()
{
	static HIDSubDescriptor nodeMouse(mouse_hidReportDescriptor, sizeof(mouse_hidReportDescriptor));
	HID().AppendDescriptor(&nodeMouse);
}

void MouseUSB::sendData(uint8_t mouse[4])
{
	mouse[0] = mouse[0] & 0x07; 				/* chop off the bits above the rightmost three in the button press */
	HID().SendReport(HID_PROTOCOL_MOUSE,mouse,4);
}
#endif