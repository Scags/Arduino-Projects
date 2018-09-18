bool g_bLit;

void setup()
{
	pinMode(9, OUTPUT);
	pinMode(7, OUTPUT);
}

void loop()
{
	delay(100);
	// Anything non-zero is true
	if (!random(0, 2))
	{
		if (g_bLit)
		{
			digitalWrite(9, LOW);
			digitalWrite(7, HIGH);
		}
		else
		{
			digitalWrite(9, HIGH);
			digitalWrite(7, LOW);
		}
		g_bLit = !g_bLit;
	}
}