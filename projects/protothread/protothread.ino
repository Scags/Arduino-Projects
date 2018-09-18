#include <TimedAction.h>

#define LED1 		9
#define LED2 		10
#define LED3 		11

void incrementNumber();
void pinFlash();

TimedAction g_Num = TimedAction(700, incrementNumber);
TimedAction g_PinFlash = TimedAction(100, pinFlash);

void setup()
{
	Serial.begin(9600);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
}

void loop()
{
	g_Num.check();
	g_PinFlash.check();
	short int i;

	for (i = 0; i <= 125; i += 5)
	{
		g_Num.check();
		g_PinFlash.check();

		analogWrite(LED1, i);
		analogWrite(LED2, (i - 125 < 0 ? -(i - 125) : i - 125));
		delay(20);
	}

	for (i = 125; i >= 0; i -= 5)
	{
		g_Num.check();
		g_PinFlash.check();

		analogWrite(LED1, i);
		analogWrite(LED2, (i - 125 < 0 ? -(i - 125) : i - 125));
		delay(20);
	}
}

void incrementNumber()
{
	static uint32_t i;
	++i;
	char *s = malloc(32 + sizeof(i));
	sprintf(s, "Hello\nI have said hello %lu times\n", i);
	Serial.print(s);
	free(s);
}

void pinFlash()
{
	static bool i;
	if (!random(0, 2))
		return;

	digitalWrite(LED3, i ? HIGH : LOW);
	i = !i;
}