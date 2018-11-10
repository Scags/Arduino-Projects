/**
 * 	On my honor, I promise that I have not received
 *	inappropriate assistance on this assignment.
 *
 *						- John Mascagni
**/

#include <Servo.h>
#include <inttypes.h>

//#define DEBUG

#define PIN_LEFTWHEEL			12
#define PIN_RIGHTWHEEL			8

#define PIN_SWITCH				7

#define PIN_DECREMENT			6
#define PIN_INCREMENT			5

#define PIN_PHOTO 	 			2
#define PIN_LED 				11

#define DO_SUBTRACTION(a) 		if (currtime - awaytime > a) { p[RIGHTWHEEL] -= 5; p[LEFTWHEEL] -= 5; }

enum
{
	STATE_WAITING = -1,
	STATE_BIO,
	STATE_CHEM,
	STATE_NANO,
	STATE_MECH,
	STATE_ELECTRIC,
	STATE_CIVIL,
	// STATE_INDUSTRIAL,
	STATE_CYBER,
	STATE_VICTORY
};

enum
{
	MOVESTATE_WAITING = -1,
	MOVESTATE_PROGRESSION,
	MOVESTATE_RETROGRESSION
};

enum
{
	LEFTWHEEL,
	RIGHTWHEEL
};

// Finally, the enum train has ended!

// Forward declaration
void checkswitch(uint32_t);
void calcphoto(uint32_t, uint16_t*);

/**
 *	Purpose: Singleton to control robot status behavior.
 *	See the first enum. Each index in the enum represents
 *	a movement behavior of the robot, starting with the
 *	movestyle that requires robot autonomy.
**/
int8_t g_iState;

/**
 *	Purpose: AKA "think" time. Using a delay() function
 *	halts all code execution, therefore using a delta
 *	timing grants fluid accuracy without pausing the program
**/
uint32_t g_iDeltaTime;

// One servo instance for each wheel
Servo servo[2];

void setup()
{
	// Defaults
	g_iState = STATE_WAITING;
	g_iDeltaTime = 0;

#ifdef DEBUG
	Serial.begin(9600);
#endif

	servo[LEFTWHEEL].attach(PIN_LEFTWHEEL);
	servo[RIGHTWHEEL].attach(PIN_RIGHTWHEEL);

	// Outputs
	pinMode(PIN_RIGHTWHEEL, OUTPUT);
	pinMode(PIN_LEFTWHEEL, OUTPUT);
	pinMode(PIN_LED, OUTPUT);

	// Inputs
	pinMode(PIN_SWITCH, INPUT);
}

void loop()
{
	uint32_t currtime = millis();	// Snag current time
	checkswitch(currtime);	// Has to happen before thinktime calculation
	uint32_t thinktime = currtime - g_iDeltaTime;

	// Motion values for servos. Defaulted to straight movement
	uint16_t rightval = 1290;
	uint16_t leftval = 1700;

#ifdef DEBUG
	static uint32_t debugtime;
	if (currtime - debugtime > 1000)
	{
		char s[64];
		sprintf(s, "currtime = %lu", currtime);
		Serial.println(s);
		sprintf(s, "thinktime = %lu", thinktime);
		Serial.println(s);
		sprintf(s, "g_iState = %d", g_iState);
		Serial.println(s);
		sprintf(s, "g_iMoveState = %d", g_iMoveState);
		Serial.println(s);
	}
#endif

	switch (g_iState)
	{
		case STATE_WAITING:		// Wait until switch is hit
			rightval = 1500;
			leftval = 1500;
			break;

		case STATE_BIO:
			if (thinktime < 500)
			{
				rightval = 1500;
				leftval = 1500;
			}
			else if (thinktime <= 1850)
			{
				// Forward motion
			}
			else if (thinktime <= 2500)
			{
				rightval -= 150;
				leftval -= 100;
			}
			else if (thinktime <= 2900)
			{
				// Forward motion
			}
			else if (thinktime <= 3500)
			{
				rightval -= 150;
				leftval -= 150;
			}
			else if (thinktime <= 3650)
			{
				// Forward motion
			}
			else if (thinktime <= 4100)
			{
				uint16_t temp = rightval;
				rightval = leftval;
				leftval = temp;
			}
			else if (thinktime <= 4450)
			{
				rightval = 1700;
				leftval = 1500;
			}
			else
			{
				++g_iState;		// To CMEN state!
				g_iDeltaTime = currtime;
			}
			break;
		case STATE_CHEM:
			if (thinktime <= 1800)
				leftval -= 40;
			else if (thinktime <= 2900)
			{
				rightval -= 150;
				leftval -= 150;
			}
			else if (thinktime <= 3500)
			{
				// Forward motion
			}
			else if (thinktime <= 4000)
				rightval += 50;
			else if (thinktime <= 4500)
			{
				rightval += 100;
				leftval += 100;
			}

			else if (thinktime <= 6000)
				rightval += 50;
			else if (thinktime <= 6300)
			{
				rightval += 50;
				leftval += 50;
			}
			else if (thinktime <= 7500)
			{
				// Forward motion
			}
			else	// We've arrived
			{
				rightval = 1500;
				leftval = 1500;
			}
			break;
		case STATE_NANO:
		case STATE_ELECTRIC:
			if (thinktime <= 500)
			{
				rightval = 1500;
				leftval = 1500;
			}
			if (thinktime <= 1700)
			{
				// Forward motion
			}
			else if (thinktime <= 3300)
			{
				uint16_t temp = rightval;
				rightval = leftval;
				leftval = temp;
			}
			else	// We've returned
			{
				rightval = 1500;
				leftval = 1500;
			}
			break;
		case STATE_MECH:
			if (thinktime <= 500)
			{
				rightval = 1500;
				leftval = 1500;
			}
			if (thinktime <= 1200)
			{
				// Forward motion
			}
			else if (thinktime <= 2000)
			{
				rightval = 1500;
				leftval += 175;
			}
			else if (thinktime <= 2700)
				leftval += 175;
			else if (thinktime <= 3000)
			{
				// Forward motion
			}
			else
			{
				leftval = 1500;
				rightval = 1500;
			}
			break;
		case STATE_CIVIL:
			break;

		case STATE_CYBER:
			int *p = malloc(sizeof(rightval) * 2);

			p[LEFTWHEEL] = leftval;
			p[RIGHTWHEEL] = rightval;

			calcphoto(currtime, p);	// Calculate photoresistance and act accordingly (if needed)

			leftval = p[LEFTWHEEL];
			rightval = p[RIGHTWHEEL];
			free(p);
			break;

		case STATE_VICTORY:
			servo[RIGHTWHEEL].writeMicroseconds(1000);
			servo[LEFTWHEEL].writeMicroseconds(2000);
			for (;;)	// Wheeeeee!
				;
			break;
	}

#ifdef DEBUG
	if (currtime - debugtime > 1000)
	{
		char s[64];
		Serial.println("Completed calculations.");
		sprintf(s, "leftval = %u\nrightval = %u\n", leftval, rightval);
		Serial.println(s);
		debugtime = currtime;
	}
#endif
	servo[RIGHTWHEEL].writeMicroseconds(rightval);
	servo[LEFTWHEEL].writeMicroseconds(leftval);
}

void calcphoto(uint32_t currtime, uint16_t *p)
{
	static uint32_t awaytime;
	uint16_t photo = analogRead(PIN_PHOTO);

#ifdef DEBUG
	char s[64];
	sprintf(s, "Photoresistance: %u", photo);
	Serial.println(s);
#endif

	if (photo <= 480)
		awaytime = 0;

	if (!awaytime)
		awaytime = currtime;

	if (currtime - awaytime >= 250)
		for (uint16_t i = 200; i <= 4000; i += 200)
			DO_SUBTRACTION(i)

	// EMERGENCY
	if (currtime - awaytime > 6000)
	{
		p[LEFTWHEEL] = 1000;
		p[RIGHTWHEEL] = 1800;
	}


	if (photo <= 480)
		digitalWrite(PIN_LED, 0);
	else digitalWrite(PIN_LED, 1);
}

void checkswitch(uint32_t currtime)
{
	static bool toggled;
	static uint32_t lasttime;
	uint8_t val = digitalRead(PIN_SWITCH);

	if (currtime - lasttime > 100)	// Avoid multiple hits at once
	{
		if (val && !toggled)
		{
			++g_iState;
#ifdef DEBUG
			Serial.println("HIT");
#endif

			toggled = true;
			g_iDeltaTime = currtime;
		}
		else if (!val)
			toggled = false;

		lasttime = currtime;
	}
}
