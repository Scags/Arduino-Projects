#include <MemoryFree.h>

#define DEFAULT_INTERVAL 1000

typedef enum
{
	State_Flash,
	State_AlternateDouble,
	State_Alternate,
	State_AlternateFast
} policelights_t;

// A knock-off version of TimedAction, smaller and quicker, but hackier
typedef struct
{
    uint32_t previous;
    uint32_t interval;
    void (*func)(void);
} timer_t;

void flashLights();
void incrementState();
// Power the pins to the according state
void powerPins_Flash(int, uint16_t, uint8_t);
void powerPins_AlternateDouble(int, uint16_t, uint8_t);
void powerPins_Alternate(uint16_t);
// timer_t function
void timer_check(timer_t*);

// Police light state is calculated through a global enum value
policelights_t g_LightState;

timer_t *g_Flash;

void setup()
{
	for (uint8_t i = 8; i <= 13; i++)
		pinMode(i, OUTPUT);

	g_Flash->previous = 0;
	g_Flash->interval = DEFAULT_INTERVAL;
	g_Flash->func = &flashLights;

	Serial.begin(9600);
}

void loop()
{
	timer_check(g_Flash);
	char s[64];
	sprintf(s, "%d", freeMemory());
	Serial.println(s);
}

void flashLights()
{
	static uint8_t counter;
	uint16_t wait = DEFAULT_INTERVAL;

	switch (g_LightState)
	{
		case State_Flash:
		{
			powerPins_Flash(!(counter % 2) ? HIGH : LOW, counter);
			++counter;
			wait = DEFAULT_INTERVAL;
			if (counter == 13)
			{
				incrementState();
				counter = 0;
				wait = DEFAULT_INTERVAL;
			}
			break;
		}
		case State_AlternateDouble:
		{
			powerPins_AlternateDouble(!(counter % 2) ? HIGH : LOW, counter);
			++counter;
			if (counter == 9)
			{
				incrementState();
				counter = 0;
				wait = DEFAULT_INTERVAL;
			}
			break;
		}
		case State_Alternate:
		{
			powerPins_Alternate(counter);
			++counter;
			if (counter == 7)
			{
				incrementState();
				counter = 0;
				wait = DEFAULT_INTERVAL;
			}
			break;
		}
		case State_AlternateFast:
		{
			powerPins_Alternate(counter);
			++counter;
			wait = DEFAULT_INTERVAL;
			if (counter == 13)
			{
				incrementState();
				counter = 0;
				wait = DEFAULT_INTERVAL;
			}
		}
	}
	g_Flash->interval = wait;
}

void incrementState()
{
	g_LightState = ( policelights_t ) g_LightState + 1;
	if (g_LightState > State_AlternateFast)
		g_LightState = State_Flash;
}

void powerPins_Flash(int val, const uint8_t counter)
{
	// Flash 3 times on the left side, then 3 times on the right

	// Left pins
	if (counter <= 6)
	{
		digitalWrite(11, val);
		digitalWrite(12, val);
		digitalWrite(13, val);
	}
	// Right pins
	else
	{
		digitalWrite(8, val);
		digitalWrite(9, val);
		digitalWrite(10, val);
	}
}

void powerPins_AlternateDouble(int val, const uint8_t counter)
{
	if (!(counter % 4))
	{
		digitalWrite(11, val);
		digitalWrite(12, val);
		digitalWrite(13, val);
	}
	else
	{
		digitalWrite(8, val);
		digitalWrite(9, val);
		digitalWrite(10, val);
	}
}

void powerPins_Alternate(const uint8_t counter)
{
	if (!(counter % 2))
	{
		digitalWrite(11, HIGH);
		digitalWrite(12, HIGH);
		digitalWrite(13, HIGH);

		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
	}
	else
	{
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);
		digitalWrite(13, LOW);

		digitalWrite(8, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(10, HIGH);
	}
}

void timer_check(timer_t *t)
{
	if ((millis() - t->previous >= t->interval))
	{
		t->previous = millis();
		t->func();
	}
}
