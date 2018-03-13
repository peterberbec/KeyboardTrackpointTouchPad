#ifndef TrackPoint_h
#define TrackPoint_h

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

class TrackPoint
{
	public:
		TrackPoint(uint8_t, uint8_t, uint8_t);
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

		uint8_t _resetPin;

#define 	_wait(x) 				while(digitalRead(_clockPin) == x)
#define 	_trueHiFalseLo(x)		((x)?_gohi(_dataPin):_golo(_dataPin))
#define 	_writeRead(x)			{_write(x); (void)_read();}
#define 	v_read()				(void)_read()

};

TrackPoint::TrackPoint(uint8_t clkPin, uint8_t dataPin, uint8_t resetPin)
{
	_clockPin = clkPin;
	_dataPin = dataPin;
	_resetPin = resetPin;
	_i = 0;
}

void TrackPoint::begin()
{
	_gohi(_clockPin);	// start clock
	_gohi(_dataPin);	// start data
	pinMode(_resetPin, OUTPUT);	// reset
	digitalWrite(_resetPin, HIGH);
	delay(2000); // empirical value
	digitalWrite(_resetPin, LOW);
	_write(SET_REMOTE_MODE);		// end reset
	v_read();
}

void TrackPoint::getData(uint8_t data[4])
{
	_writeRead(REQUEST_DATA);
	data[0] |= _read();
	_i = _read();
	if(_i != 0) data[1] = _i;
	_i = -_read();
	if(_i != 0) data[2] = _i;
}

void TrackPoint::_golo(uint8_t pin)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void TrackPoint::_gohi(uint8_t pin)
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void TrackPoint::_write(uint8_t data)
{
	uint8_t parityBit = 0x01;

	_gohi(_dataPin);
	_gohi(_clockPin);
	delayMicroseconds(300);
	_golo(_clockPin);
	delayMicroseconds(300);
	_golo(_dataPin);
	delayMicroseconds(10);
	_gohi(_clockPin);	// start bit
	_wait(HIGH);	/* wait for device to take control of clock */
	for(_i = 0; _i < 8; _i++) 	// clear to send data
	{
		_trueHiFalseLo(data & 0x01);
		_wait(LOW); // wait for clock
		_wait(HIGH);
		parityBit = parityBit ^ (data & 0x01);
		data = data >> 1;
	}
	_trueHiFalseLo(parityBit); // parity bit
	_wait(LOW); // clock cycle - like ack.
	_wait(HIGH);
	_gohi(_dataPin); // stop bit
	delayMicroseconds(50);
	_wait(HIGH);
	while((digitalRead(_clockPin) == LOW) || (digitalRead(_dataPin) == LOW)); // mode switch
	_golo(_clockPin);// hold up incoming data
}

uint8_t TrackPoint::_read()
{
	uint8_t data = 0x00;

	_gohi(_clockPin);
	_gohi(_dataPin);
	delayMicroseconds(50);
	_wait(HIGH);
	delayMicroseconds(5); // not sure why.
	_wait(LOW);

	for(_i = 0; _i < 8; _i++)
	{
		_wait(HIGH);
		data = data | (digitalRead(_dataPin) << _i);
		_wait(LOW);
	}
	
	_wait(HIGH);	// eat parity bit, ignore it.
	_wait(LOW);
	_wait(HIGH);	// eat stop bit
	_wait(LOW);
	_golo(_clockPin);	// hold incoming data

	return data;
}
#endif
