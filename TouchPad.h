#ifndef TouchPad_h
#define TouchPad_h

#define SET_RESOLUTION			0xE8
#define REQUEST_DATA			0xEB
#define SET_REMOTE_MODE			0xF0
#define GET_DEVICE_ID			0xF2
#define SET_SAMPLE_RATE			0xF3
#define SAMPLE_RATE				0x28
#define RESET					0xFF
#define INTELLI_MOUSE			0x03
#define SET_SCALING_TO_1_TO_1		0xE6
#define RESOLUTION_8_COUNTS_PER_MM	0x03

class TouchPad
{
	public:
		TouchPad(uint8_t, uint8_t);
		void begin();
		void getData(uint8_t[4]);
		
	private:
		uint8_t _clockPin;
		uint8_t _dataPin;
		uint8_t _i;
				
		void _golo(uint8_t);
		void _gohi(uint8_t);
		
		void _write(uint8_t);
		uint8_t _read();

		bool _intelliMouse;	
		bool _intelliMouseCheck();

#define 	_wait(x) 				while(digitalRead(_clockPin) == x)
#define 	_trueHiFalseLo(x)		((x)?_gohi(_dataPin):_golo(_dataPin))
#define 	_writeRead(x)			{_write(x); (void)_read();}
#define 	v_read()				(void)_read()

};

TouchPad::TouchPad(uint8_t clockPin, uint8_t dataPin)
{
	_clockPin = clockPin;
	_dataPin = dataPin;
	_i = 0;
}

void TouchPad::begin()
{
	_gohi(_clockPin);	// start clock
	_gohi(_dataPin);	// start data
	_writeRead(RESET); // Reset
	v_read();	// self-test state
	v_read();	// mouse ID
	_intelliMouse = _intelliMouseCheck();
	_writeRead(SET_RESOLUTION);
	_writeRead(RESOLUTION_8_COUNTS_PER_MM);
	_writeRead(SET_SCALING_TO_1_TO_1);
	_writeRead(SET_SAMPLE_RATE);
	_writeRead(SAMPLE_RATE);
	_writeRead(SET_REMOTE_MODE);
	v_read(); /* original -> */ /*	delay(500); */
}

void TouchPad::getData(uint8_t data[4])
{	
	_writeRead(REQUEST_DATA);
	data[0] = _read();					/* buttons */
	data[1] = _read();					/* x */
	data[2] = -_read();					/* y is negative. no clue why */
	data[3] = (_intelliMouse)?-_read():0;	/* everyone loves trinary operators! */
}

void TouchPad::_golo(uint8_t pin)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void TouchPad::_gohi(uint8_t pin)
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void TouchPad::_write(uint8_t data)
{
	uint8_t parityBit = 0x01;

	_gohi(_dataPin);
	_gohi(_clockPin);
	delayMicroseconds(300);
	_golo(_clockPin);
	delayMicroseconds(300);
	_golo(_dataPin);
	delayMicroseconds(10);
	_gohi(_clockPin); // start bit
	_wait(HIGH);		/* original ->> *//* _wait(LOW); */
	for(_i = 0; _i < 8; _i++)	 // data
	{
		_trueHiFalseLo(data & 0x01);
		_wait(LOW); // wait for clock
		_wait(HIGH);
		parityBit = parityBit ^ (data & 0x01);
		data = data >> 1;
	}
	_trueHiFalseLo(parityBit);
	_wait(LOW); // clock cycle - like ack.
	_wait(HIGH);
	_gohi(_dataPin); // stop bit
	delayMicroseconds(50);
	_wait(HIGH);		/* original ->> *//* _wait(LOW); */
	while((digitalRead(_clockPin) == LOW) || (digitalRead(_dataPin) == LOW));
	_golo(_clockPin); // put a hold on the incoming data
}

uint8_t TouchPad::_read()
{
	uint8_t data = 0x00;

	_gohi(_clockPin);
	_gohi(_dataPin);
	delayMicroseconds(50);
	_wait(HIGH);	/* original ->> *//* _wait(LOW); */
	delayMicroseconds(5);
	_wait(LOW); /* original ->> *//* _wait(HIGH); */ // consume the start bit

	for(_i = 0; _i < 8; _i++) // consume 8 bits of data
	{
		_wait(HIGH);
		data = data | (digitalRead(_dataPin) << _i);
		_wait(LOW);
	}

	_wait(HIGH);	// eat parity bit, ignore it.
	_wait(LOW);
	_wait(HIGH);	// eat stop bit
	_wait(LOW);
	_golo(_clockPin); // put a hold on the incoming data

	return data;
}

bool TouchPad::_intelliMouseCheck()	 // IntelliMouse detection sequence
{	// Don't ask - 200 100 80 is magic
	_writeRead(SET_SAMPLE_RATE);
	_writeRead(200);
	_writeRead(SET_SAMPLE_RATE);
	_writeRead(100);
	_writeRead(SET_SAMPLE_RATE);
	_writeRead(80);

	_writeRead(GET_DEVICE_ID);
	return (_read() == INTELLI_MOUSE);
}
#endif
