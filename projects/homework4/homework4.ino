#define LED1 		8
#define LED2 		9

void setup()
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
}

void loop()
{
	int i;
	for (i = 0; i < 12; i++)
	{
		digitalWrite(LED1, HIGH);
		digitalWrite(LED2, LOW);

		delay(200);

		digitalWrite(LED2, HIGH);
		digitalWrite(LED1, LOW);

		delay(200);
	}

	digitalWrite(LED2, LOW);

	delay(750);

	for (i = 0; i < 6; i++)
	{
		digitalWrite(LED1, HIGH);
		digitalWrite(LED2, LOW);

		delay(500);

		digitalWrite(LED2, HIGH);
		digitalWrite(LED1, LOW);

		delay(500);
	}

	digitalWrite(LED2, LOW);

	delay(1000);
}