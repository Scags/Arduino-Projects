#ifndef SCAG
#define SCAG

/**
 *	@brief Power an array of pins.
 *
 *	@param pins 				Array of pin indices to write to.
 *	@param val 					Voltage to write to pins
 *	@param wait 				if a delay is needed, passed optionally.
 *
 *	@noreturn
*/
void writePins(uint8_t pins[], size_t len, int val, int wait = 0)
{
	uint8_t i;

	for (i = 0; i < len; i++)
		digitalWrite(pins[i], val);

	if (wait)
		delay(wait);
}

/**
 *	@brief Read the input of an array of pins.
 *
 *	@param pins 				Array of pin indices to read from.
 *	@param wait 				If a delay is needed, passed optionally.
 *
 *	@return 					Pointer to input array. This MUST be free()'d.
*/
int *readPins(uint8_t pins[], size_t len, int wait = 0)
{
	int *p = (int *) malloc(len * sizeof(int));
	if (!p)
		return NULL;

	uint8_t i;

	for (i = 0; i < len; i++)
		p[i] = digitalRead(pins[i]);

	if (wait)
		delay(wait);

	return p;
}

/**
 *	@brief Read the input of an array of pins and writes it to an array.
 *
 *	@param pins 				Array of pins indices to read from.
 *	@param pins2 				Array of pin reads to write to.
 *	@param len 					Size of the first array passed.
 *	@param wait 				If a delay is needed, passed optionally.
 *
 *	@noreturn
*/
void readPinsEx(uint8_t pins[], size_t len, uint8_t pins2[], int wait = 0)
{
	uint8_t i;

	for (i = 0; i < len; i++)
		pins2[i] = digitalRead(pins[i]);

	if (wait)
		delay(wait);
}

/**
 *	@brief Return a random integer with an inclusive high.
 *
 *	@param low 					Lowest number.
 *	@param high 				Highest number.
*/
long randomInt(int low, int high)
{
	return random(low, high+1);
}

#endif 	// SCAG