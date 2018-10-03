#include <Servo.h>

#define PIN_LEFT 8
#define PIN_RIGHT 12
#define BASIC_PULSE 1000

enum
{
	LEFTWHEEL,
	RIGHTWHEEL
};

Servo servo[2];

void motion(uint8_t, int8_t);
void clamp(int*, int, int);

void setup()
{
	servo[LEFTWHEEL].attach(PIN_LEFT);
	servo[RIGHTWHEEL].attach(PIN_RIGHT);
}

void loop()
{

}

void motion(uint8_t serv, short degree)
{
	// clamp(&degree, 200, -200);
	servo[serv].write(degree);
}

void clamp(int *c, int max, int min)
{
	if (c > max)
		c = max;
	else if (c < min)
		c = min;
}
