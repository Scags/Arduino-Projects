#define PIN_INPUT     7
#define PIN_OUTPUT1   8
#define PIN_OUTPUT2   9

void setup()
{
	pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_OUTPUT1, OUTPUT);
  pinMode(PIN_OUTPUT2, OUTPUT);
}

void loop()
{
	uint8_t val = digitalRead(PIN_INPUT);
  // Write to other output pin the opposite of the pin read
  // !HIGH is equal to LOW and vice versa
  digitalWrite(PIN_OUTPUT2, !val);
  // If digitalRead() returns something other than 0 or LOW
  if (val)
  {
    // Repetir diez
    for (uint8_t i = 0; i < 10; ++i)
    {
      digitalWrite(PIN_OUTPUT1, HIGH);
      delay(300);
      digitalWrite(PIN_OUTPUT1, LOW);
      delay(100);
    }
  }
}
