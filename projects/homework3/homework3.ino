void setup()
{
	Serial.begin(9600);
}

void loop()
{
	static uint32_t i;
	++i;
	char *s = malloc(32 + sizeof(i));
	sprintf(s, "Hello\nI have said hello %lu times\n", i);
	Serial.print(s);
	free(s);
}