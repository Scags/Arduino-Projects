#include "scag.h"

#define NUM_PINS 6

uint8_t g_iPins[NUM_PINS] = {
	8,
	9,
	10,
	11,
	12,
	13
};

void powerLeft(int, int = 0);
void powerRight(int, int = 0);

void setup()
{
	for (uint8_t i = 0; i < NUM_PINS; i++)
		pinMode(g_iPins[i], OUTPUT);
}

void loop()
{
	uint8_t i, u;

	for (u = 0; u < 2; u++)
	{
		for (i = 0; i < 3; i++)
		{
			powerLeft(HIGH, 100);
			powerLeft(LOW, 100);
		}
	
		for (i = 0; i < 3; i++)
		{
			powerRight(HIGH, 100);
			powerRight(LOW, 100);
		}
	}

	delay(100);

	for (i = 0; i < 8; i++)
	{
		powerLeft(HIGH);
		powerRight(LOW, 100);
		powerLeft(LOW);
		powerRight(HIGH, 100);
	}
	powerRight(LOW, 100);
}

void powerRight(int val, int wait)
{
	digitalWrite(8, val);
	digitalWrite(9, val);
	digitalWrite(10, val);
	if (wait)
		delay(wait);
}

void powerLeft(int val, int wait)
{
	digitalWrite(11, val);
	digitalWrite(12, val);
	digitalWrite(13, val);
	if (wait)
		delay(wait);
}