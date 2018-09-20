#ifndef SCAG
#define SCAG

#define repeat(a) 	for (uint16_t i = 0; i < a; ++i)

/**
 *	@brief digitalWrite to an array of pins.
 *
 *	@param pins 				Array of pin indices to write to.
 *	@param len 					Size of pins array.
 *	@param val 					Voltage to write to pins
 *
 *	@noreturn
*/
void digitalWriteEx(int pins[], size_t len, int val)
{
	uint8_t i;

	for (i = 0; i < len; i++)
		digitalWrite(pins[i], val);
}

/**
 *	@brief analogWrite to an array of pins.
 *
 *	@param pins 				Array of pin indices to write to.
 *	@param len 					Size of pins array.
 *	@param val 					Voltage to write to pins
 *
 *	@noreturn
*/
void analogWriteEx(int pins[], size_t len, int val)
{
	uint8_t i;

	for (i = 0; i < len; i++)
		analogWrite(pins[i], val);
}

/**
 *	@brief digitalRead the input of an array of pins.
 *
 *	@param pins 				Array of pin indices to read from.
 *	@param len 					Size of pins array.
 *
 *	@return 					Pointer to input array.
*/
int *digitalReadEx(int pins[], size_t len)
{
	int *p = ( int * ) malloc(len * sizeof(int));
	if (!p)
		return NULL;

	uint8_t i;

	for (i = 0; i < len; i++)
		p[i] = digitalRead(pins[i]);

	return p;
}

/**
 *	@brief analogRead the input of an array of pins.
 *
 *	@param pins 				Array of pin indices to read from.
 *	@param len 					Size of pins array.
 *
 *	@return 					Pointer to input array.
*/
int *analogReadEx(int pins[], size_t len)
{
	int *p = ( int * ) malloc(len * sizeof(int));
	if (!p)
		return NULL;

	uint8_t i;

	for (i = 0; i < len; i++)
		p[i] = analogRead(pins[i]);

	return p;
}

/**
 *	@brief Return a random integer with an inclusive high.
 *
 *	@param low 					Lowest number.
 *	@param high 				Highest number.
 *
 *	@return 					Random number between inclusive low and inclusive high
*/
long randomInt(long low, long high)
{
	return random(low, high+1);
}

/**
 *	@brief Set the pinMode of an array of pins.
 *
 *	@param pins 				Array of pins
 *	@param len 					Size of pin array.
 *	@param val 					INPUT or OUTPUT.
 *
 *	@noreturn
*/
void pinModeEx(int pins[], size_t len, int val)
{
	uint8_t i;
	for (i = 0; i < len; i++)
		pinMode(pins[i], val);
}

/**
 *	@brief Clamp a value between 2 other values.
 *
 *	@param val 				Pointer to the value being clamped.
 *	@param low 				Low value.
 *	@param high 			High value.
 *
 *	@noreturn
*/
void clamp(long *val, long low, long high)
{
	if (val < low)
		val = low;
	else if (val > high)
		val = high;
}

#endif 	// SCAG