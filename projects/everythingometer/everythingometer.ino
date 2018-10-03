#include <SFE_MicroOLED.h>

#define PIN_LED1 		9
#define PIN_LED2 		8
#define PIN_BUTTON 		2

void changestate();

typedef enum
{
	State_TemperatureF,
	State_TemperatureC,
	State_Humidity,
	STATE_LENGTH
} pinstate_t;

// Global singleton to handle display option
volatile pinstate_t g_PinState;

MicroOLED led(PIN_LED1, PIN_LED2);

void setup()
{
	led.begin();
	delay(1000);
	led.clear(ALL);
	led.display();
	led.clear(PAGE);
	led.display();
	led.setFontType(1); 
	led.setCursor(0, 0);
	
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), changestate, RISING);	
}

void loop()
{
	delay(100);

	switch (g_PinState)
	{
		case State_TemperatureF:
		case State_TemperatureC:
		{
			float temp;
			bool c;

			temp = analogRead(0);
			c = g_PinState == State_TemperatureC;

			temp = (5.0 * temp * 1000.0) / (1024 * 10);
			temp = c ? temp : (temp * 9 / 5 + 32);

			// Size of float + size of 1 character + 1 for null terminator
			char *buffer = ( char * ) malloc(sizeof(temp) + sizeof(char) + 1);
			if (!buffer)
				return;

			sprintf(buffer, "%0.1f%c", temp, (c ? 'C' : 'F'));
			led.print(buffer);
			free(buffer);

			break;
		}
		case State_Humidity:
		{

			break;
		}
	}
}

void changestate()
{
	g_PinState = /*static_cast< pinstate_t >*/ ( pinstate_t ) g_PinState + 1;

	if (g_PinState == STATE_LENGTH)
		g_PinState = State_TemperatureF;
}
