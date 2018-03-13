#ifndef PS2Mouse_h
#define PS2Mouse_h

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

class PS2Mouse
{
	public:
		PS2Mouse(uint8_t, uint8_t, uint8_t);
		PS2Mouse(uint8_t, uint8_t);
		void begin();
		void getData();
		
	private:
		uint8_t _clockPin;
		uint8_t _dataPin;
		uint8_t _i;
				
		void _golo(uint8_t);
		void _gohi(uint8_t);
		
		void _write(uint8_t);
		uint8_t _read();

		uint8_t _resetPin;

		bool _intelliMouse;	
		bool _intelliMouseCheck();

#define 	_wait(x) 				while(digitalRead(_clockPin) == x)
#define 	_trueHiFalseLo(x)		((x)?_gohi(_dataPin):_golo(_dataPin))
#define 	_writeRead(x)			{_write(x); (void)_read();}
#define 	v_read()				(void)_read()

};

PS2Mouse::PS2Mouse(uint8_t clockPin, uint8_t dataPin, uint8_t resetPin) /* TrackPoint */
{
	_clockPin = clockPin;
	_dataPin = dataPin;
	_resetPin = resetPin;
	_i = 0;
}

PS2Mouse::PS2Mouse(uint8_t clockPin, uint8_t dataPin)
{
	_clockPin = clockPin;
	_dataPin = dataPin;
	_resetPin = 0;
	_i = 0;
}

void PS2Mouse::begin()
{
	_gohi(_clockPin);			/* start clock */
	_gohi(_dataPin);			/* start data */
	if(_resetPin)				/* we're an eraser */
	{
		pinMode(_resetPin, OUTPUT);	/* reset */
		digitalWrite(_resetPin, HIGH);
		delay(2000); 				/* empirical value */
		digitalWrite(_resetPin, LOW);
		_intelliMouse = 0;
	}
	else						/* or we're a PS2 mouse */
	{
		_writeRead(RESET); 	/* Reset */
		v_read();			/* self-test state */
		v_read();			/* mouse ID */
		_intelliMouse = _intelliMouseCheck();
		_writeRead(SET_RESOLUTION);
		_writeRead(RESOLUTION_8_COUNTS_PER_MM);
		_writeRead(SET_SCALING_TO_1_TO_1);
		_writeRead(SET_SAMPLE_RATE);
		_writeRead(SAMPLE_RATE);		
	}
	_writeRead(SET_REMOTE_MODE);
	v_read();
}

void PS2Mouse::getData()
{	
	_writeRead(REQUEST_DATA);
	mouseData[0] |= _read();			/* buttons */
	if(( _i=_read() ))
	{
		mouseData[1] = _i;			/* x */
	}
	if(( _i = -_read() ))
	{
		mouseData[2] = _i;			/* y is negative. no clue why */
	}
	if(_intelliMouse)				/* if we have fancy mouse */
	{
		mouseData[3] = -_read();		/* wheel is negative too. */
	}
	else
	{
		mouseData[3] = 0;
	}
}

void PS2Mouse::_golo(uint8_t pin)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void PS2Mouse::_gohi(uint8_t pin)
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void PS2Mouse::_write(uint8_t data)
{
	uint8_t parityBit = 0x01;

	_gohi(_dataPin);
	_gohi(_clockPin);
	delayMicroseconds(300);
	_golo(_clockPin);
	delayMicroseconds(300);
	_golo(_dataPin);
	delayMicroseconds(10);
	_gohi(_clockPin); 	/* start bit */
	_wait(HIGH);
	
	for(_i = 0; _i < 8; _i++)
	{				/* data */
		_trueHiFalseLo(data & 0x01);
		_wait(LOW); 	/* wait for clock */
		_wait(HIGH);
		parityBit = parityBit ^ (data & 0x01);
		data = data >> 1;
	}
	
	_trueHiFalseLo(parityBit);
	_wait(LOW); 		/* clock cycle - like ack. */
	_wait(HIGH);
	_gohi(_dataPin); 	/* stop bit */
	delayMicroseconds(50);
	_wait(HIGH);
	while((digitalRead(_clockPin) == LOW) || (digitalRead(_dataPin) == LOW));
	_golo(_clockPin); 	/* put a hold on the incoming data */
}

uint8_t PS2Mouse::_read()
{
	uint8_t data = 0x00;

	_gohi(_clockPin);
	_gohi(_dataPin);
	delayMicroseconds(50);
	_wait(HIGH);
	delayMicroseconds(5);
	_wait(LOW); 		/* consume the start bit */

	for(_i = 0; _i < 8; _i++)
	{				/* consume 8 bits of data */
		_wait(HIGH);
		data = data | (digitalRead(_dataPin) << _i);
		_wait(LOW);
	}

	_wait(HIGH);		/* eat parity bit. parity errors are another nightmare for later */
	_wait(LOW);
	_wait(HIGH);		/* eat stop bit */
	_wait(LOW);
	_golo(_clockPin); 	/* put a hold on the incoming data */

	return data;
}

bool PS2Mouse::_intelliMouseCheck()	 /* IntelliMouse detection sequence */
{	/* Don't ask - 200 100 80 is magic wheel detection sequence */
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
