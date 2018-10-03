#define LEFTWHEEL       12
#define RIGHTWHEEL      8
#define PULSE           1000
#define TURN_PULSE		600

void setup()
{
	pinMode(LEFTWHEEL, OUTPUT);
	pinMode(RIGHTWHEEL, OUTPUT);
}

void loop()
{
	uint8_t i;
	for (i = 0; i < 100; ++i)
	{
		digitalWrite(LEFTWHEEL, HIGH);
		digitalWrite(RIGHTWHEEL, HIGH);
		delayMicroseconds(PULSE);
		digitalWrite(LEFTWHEEL, LOW);
		delayMicroseconds(PULSE);
		digitalWrite(RIGHTWHEEL, LOW);
		delay(20);
	}
	for (i = 0; i < 100; ++i)
	{
		digitalWrite(LEFTWHEEL, HIGH);
		digitalWrite(RIGHTWHEEL, HIGH);
		delayMicroseconds(PULSE);
		digitalWrite(LEFTWHEEL, LOW);
		delayMicroseconds(TURN_PULSE);
		digitalWrite(RIGHTWHEEL, LOW);
		delay(20);
	}
}
