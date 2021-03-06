/*
 * taken from USB HID spec
 */

#define	HID_RESERVED	0x00
#define	HID_ERROR_ROLLOVER	0x01
#define	HID_POSTFAIL	0x02
#define	HID_ERROR_UNDEFINED	0x03	
#define	HID_A	0x04
#define	HID_B	0x05
#define	HID_C	0x06
#define	HID_D	0x07
#define	HID_E	0x08
#define	HID_F	0x09
#define	HID_G	0x0A
#define	HID_H	0x0B
#define	HID_I	0x0C
#define	HID_J	0x0D
#define	HID_K	0x0E
#define	HID_L	0x0F
#define	HID_M	0x10
#define	HID_N	0x11
#define	HID_O	0x12
#define	HID_P	0x13
#define	HID_Q	0x14
#define	HID_R	0x15
#define	HID_S	0x16
#define	HID_T	0x17
#define	HID_U	0x18
#define	HID_V	0x19
#define	HID_W	0x1A
#define	HID_X	0x1B
#define	HID_Y	0x1C
#define	HID_Z	0x1D
#define	HID_1	0x1E
#define	HID_2	0x1F
#define	HID_3	0x20
#define	HID_4	0x21
#define	HID_5	0x22
#define	HID_6	0x23
#define	HID_7	0x24
#define	HID_8	0x25
#define	HID_9	0x26
#define	HID_0	0x27
#define	HID_ENTER	0x28
#define	HID_ESCAPE	0x29
#define	HID_BACKSPACE	0x2A
#define	HID_TAB	0x2B
#define	HID_SPACEBAR	0x2C	
#define	HID_DASH_UNDERSCORE	0x2D
#define	HID_EQUAL_PLUS	0x2E
#define	HID_OPENBRACKET_OPENBRACE	0x2F
#define	HID_CLOSEBRACKET_CLOSEBRACE	0x30
#define	HID_BACKSLASH_PIPE	0x31
#define	HID_POUND_TILDE	0x32
#define	HID_SEMICOLON_COLON	0x33
#define	HID_BACKTICK_DOUBLE_BACKTICK	0x34
#define	HID_ACCENT_GRAVE_TILDE	0x35
#define	HID_COMMA_LESS_THAN	0x36
#define	HID_PERIOD_GREATER_THAN	0x37
#define	HID_FRONT_SLASH_QUESTION_MARK	0x38
#define	HID_CAPS_LOCK				0x39
#define	HID_F1					0x3A
#define	HID_F2					0x3B
#define	HID_F3					0x3C
#define	HID_F4					0x3D
#define	HID_F5					0x3E
#define	HID_F6	0x3F
#define	HID_F7	0x40
#define	HID_F8	0x41
#define	HID_F9	0x42
#define	HID_F10	0x43
#define	HID_F11	0x44
#define	HID_F12	0x45
#define	HID_PRINT_SCREEN	0x46
#define	HID_SCROLL_LOCK	0x47
#define	HID_PAUSE	0x48
#define	HID_INSERT	0x49
#define	HID_HOME	0x4A
#define	HID_PAGEUP	0x4B
#define	HID_DELETE	0x4C
#define	HID_END	0x4D
#define	HID_PAGE_DOWN	0x4E
#define	HID_RIGHT_ARROW	0x4F
#define	HID_LEFT_ARROW	0x50
#define	HID_DOWN_ARROW	0x51
#define	HID_UP_ARROW	0x52
#define	HID_PAD_NUMLOCK_CLEAR	0x53
#define	HID_PAD_FRONT_SLASH	0x54
#define	HID_PAD_ASTERIX	0x55
#define	HID_PAD_MINUS	0x56
#define	HID_PAD_PLUS	0x57
#define	HID_PAD_ENTER	0x58
#define	HID_PAD_1_END	0x59
#define	HID_PAD_2_DOWN_ARRoW	0x5A
#define	HID_PAD_3_PAGE_DOWN	0x5B
#define	HID_PAD_4_LEFT_ARROW	0x5C
#define	HID_PAD_5	0x5D
#define	HID_PAD_6_RIGHT_ARROW	0x5E
#define	HID_PAD_7_HOME	0x5F
#define	HID_PAD_8_UP_ARROW	0x60
#define	HID_PAD_9_PAGE_UP	0x61
#define	HID_PAD_0_INSERT	0x62
#define	HID_PAD_PERIOD_DELETE	0x63	
#define	HID_BACKSLASH_PIPE	0x64
#define	HID_APPLICATION	0x65
#define	HID_POWER	0x66
#define	HID_PAD_EQUAL	0x67
#define	HID_F13	0x68
#define	HID_F14	0x69
#define	HID_F15	0x6A
#define	HID_F16	0x6B
#define	HID_F17	0x6C
#define	HID_F18	0x6D
#define	HID_F19	0x6E
#define	HID_F20	0x6F
#define	HID_F21	0x70
#define	HID_F22	0x71
#define	HID_F23	0x72
#define	HID_F24	0x73
#define	HID_EXECUTE	0x74
#define	HID_HELP	0x75
#define	HID_MENU	0x76
#define	HID_SELECT	0x77
#define	HID_STOP	0x78
#define	HID_AGAIN	0x79
#define	HID_UNDO	0x7A
#define	HID_CUT	0x7B
#define	HID_COPY	0x7C
#define	HID_PASTE	0x7D
#define	HID_FIND	0x7E
#define	HID_MUTE	0x7F
#define	HID_VOLUME_UP	0x80
#define	HID_VOLUME_DOWN	0x81
#define	HID_LOCKING_CAPS_LOCK	0x82
#define	HID_LOCKING_NUM_LOCK	0x83
#define	HID_LOCKING_SCROLL_LOCK	0x84
#define	HID_PAD_COMMA	0x85
#define	HID_PAD_EQUAL	0x86
#define	HID_INTERNATIONAL_1	0x87
#define	HID_INTERNATIONAL_2	0x88
#define	HID_INTERNATIONAL_3	0x89
#define	HID_INTERNATIONAL_4	0x8A
#define	HID_INTERNATIONAL_5	0x8B
#define	HID_INTERNATIONAL_6	0x8C
#define	HID_INTERNATIONAL_7	0x8D
#define	HID_INTERNATIONAL_8	0x8E
#define	HID_INTERNATIONAL_9	0x8F
#define	HID_LANG_1	0x90
#define	HID_LANG_2	0x91
#define	HID_LANG_3	0x92
#define	HID_LANG_4	0x93
#define	HID_LANG_5	0x94
#define	HID_LANG_6	0x95
#define	HID_LANG_7	0x96
#define	HID_LANG_8	0x97
#define	HID_LANG_9	0x98
#define	HID_ALTERNATE_ERASE	0x99
#define	HID_SYSREQ_ATTENTION	0x9A
#define	HID_CANCEL	0x9B
#define	HID_CLEAR	0x9C
#define	HID_PRIOR	0x9D
#define	HID_RETURN	0x9E
#define	HID_SEPARATOR	0x9F
#define	HID_OUT	0xA0
#define	HID_KEY_OPER	0xA1
#define	HID_CLEAR_AGAIN	0xA2
#define	HID_CRSEL_RPOPS	0xA3
#define	HID_EXSEL	0xA4
#define	HID_RESERVED1	0xA5
#define	HID_RESERVED2	0xA6
#define	HID_RESERVED3	0xA7
#define	HID_RESERVED4	0xA8
#define	HID_RESERVED5	0xA9
#define	HID_RESERVED6	0xAA
#define	HID_RESERVED7	0xAB
#define	HID_RESERVED8	0xAC
#define	HID_RESERVED9	0xAD
#define	HID_RESERVED10	0xAE
#define	HID_RESERVED11	0xAF
#define	HID_PAD_00	0xB0
#define	HID_PAD_000	0xB1
#define	HID_THOUSANDS_SEPARATOR	0xB2
#define	HID_DECIMAL_SEPARATOR	0xB3
#define	HID_CURRENCY_UNIT	0xB4
#define	HID_CURRENCY_SUBUNIT	0xB5
#define	HID_PAD_OPEN_PAREN	0xB6
#define	HID_PAD_CLOSE_PAREN	0xB7
#define	HID_PAD_OPEN_BRACE	0xB8
#define	HID_PAD_CLOSE_BRACE	0xB9
#define	HID_PAD_TAB	0xBA
#define	HID_PAD_BACKSPACE	0xBB
#define	HID_PAD_A	0xBC
#define	HID_PAD_B	0xBD
#define	HID_PAD_C	0xBE
#define	HID_PAD_D	0xBF
#define	HID_PAD_E	0xC0
#define	HID_PAD_F	0xC1
#define	HID_PAD_XOR	0xC2
#define	HID_PAD_CARAT	0xC3
#define	HID_PAD_PERCENT	0xC4
#define	HID_PAD_LESS_THAN	0xC5
#define	HID_PAD_GREATER_THAN	0xC6
#define	HID_PAD_AMPERSAND	0xC7
#define	HID_PAD_DOUBLE_AMPERSAND	0xC8
#define	HID_PAD_PIPE				0xC9
#define	HID_PAD_DOUBLE_PIPE			0xCA
#define	HID_PAD_COLON				0xCB
#define	HID_PAD_POUND				0xCC
#define	HID_PAD_SPACE				0xCD
#define	HID_PAD_AT				0xCE
#define	HID_PAD_EXCLIMATION_POINT	0xCF
#define	HID_PAD_MEMORY_STORE	0xD0
#define	HID_PAD_MEMORY_RECALL	0xD1
#define	HID_PAD_MEMORY_CLEAR	0xD2
#define	HID_PAD_MEMORY_ADD	0xD3
#define	HID_PAD_MEMORY_SUBTRACT	0xD4
#define	HID_PAD_MEMORY_MULTIPLY	0xD5
#define	HID_PAD_MEMORY_DIVIDE	0xD6
#define	HID_PAD_PLUS_MINUS	0xD7
#define	HID_PAD_CLEAR	0xD8
#define	HID_PAD_CLEAR_ENTRY	0xD9
#define	HID_PAD_BINARY	0xDA
#define	HID_PAD_OCTAL	0xDB
#define	HID_PAD_DECIMAL	0xDC
#define	HID_PAD_HEXADECIMAL	0xDD
#define	HID_RESERVED12	0xDE
#define	HID_RESERVED13	0xDF
#define	HID_LEFT_CONTROL	0xE1
#define	HID_LEFT_SHIFT	0xE2
#define	HID_LEFT_ALT	0xE3
#define	HID_LEFT_GUI	0xE4
#define	HID_RIGHT_CONTROL	0xE5
#define	HID_RIGHT_SHIFT	0xE6
#define	HID_RIGHT_ALT	0xE6
#define	HID_RIGHT_GUI	0xE7
