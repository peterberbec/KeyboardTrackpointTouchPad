#ifndef HID_Keyboard_Usage_Codes_h
#define HID_Keyboard_Usage_Codes_h

#define NKRO_ID	2

const uint8_t nkro_descriptor[25] PROGMEM= {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, NKRO_ID,                 //   REPORT_ID(2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0xe8,                    //   REPORT_COUNT (232) 232 bits = 29 bytes.
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
} ;


/*
 * The HID specification defines 232 usage codes, so we need a 232-bit vector.
 * 232 bits is (conveniently) exactly 29 bytes.
 * 
 */

#define NKRO_REPORT_SIZE	29

uint8_t nkro_report[NKRO_REPORT_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00
} ;

#define KEY_BREAK 0x80
#define KEY_CODE 0x7F

#define SET(TBL,C) (TBL[C >> 3] |= (1 << (C & 0x07))) 
#define UNSET(TBL,C) (TBL[C >> 3] &= ~(1 << (C & 0x07)))

/* part of ThinkpadKeyboard::ThinkpadKeyboard() */
static HIDSubDescriptor nkroKeyboard(nkro_reportdescriptor, sizeof nkro_reportdescriptor);
HID().AppendDescriptor(&nkroKeyboard);
/* end part of ThinkpadKeyboard::ThinkpadKeyboard() */

void _press(uint8_t key) {

  /*
   *  The SET and UNSET macros potentially evaluate
   *  C twice, hence the local variable here.
   *
   */

  unsigned char tempKey = (key & KEY_CODE) ;

  if (tempKey & KEY_BREAK) 
    UNSET(nkro_report, tempKey) ;
  else
    SET(nkro_report, tempKey) ;

} 

void _pressKeys()
{
	while(numKeysCurrentlyPressed > 0)
	{
		update_report(keysCurrentlyPressed[numKeysCurrentlyPressed-1]) ;             //   Update the HID Report
		numKeysCurrentlyPressed--;
	}
}

void sendData()
{
	HID().SendReport(NKRO_ID,nkro_report, NKRO_REPORT_SIZE)
	memcpy(nkro_report,0,NKRO_REPORT_SIZE);
}
#endif
