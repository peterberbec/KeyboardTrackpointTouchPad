#ifndef keyboardUSB_h
#define keyboardUSB_h

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

class KeyboardUSB
{
	public:
		KeyboardUSB();
		void begin();
		void sendData(KeyReport);
};

KeyboardUSB::KeyboardUSB()
{
}

void KeyboardUSB::begin()
{
	static HIDSubDescriptor nodeKeyboard(keyboard_hidReportDescriptor, sizeof(keyboard_hidReportDescriptor));
	HID().AppendDescriptor(&nodeKeyboard);
}

void KeyboardUSB::sendData(KeyReport k)
{
	HID().SendReport(HID_PROTOCOL_KEYBOARD,&k,sizeof(k));
}
#endif
