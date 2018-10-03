#include <NewPing.h>
#include <SFEMP3Shield.h>
 
#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200 
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SdFat sd;
SFEMP3Shield MP3player;
 
void setup()
{
	Serial.begin(9600);
	initSD();  // Initialize the SD card
	initMP3Player();
}
 
void loop()
{
	delay(50);
	if (sonar.ping_cm() < 70)
	{
		switch (MP3player.playMP3("doorbell.mp3", 0))
		{
			case 3:Serial.println("couldnt read MP3_RESET");break;
			case 2:Serial.println("couldnt open file");break;
		}
	}
}

void initMP3Player()
{
	uint8_t result = MP3player.begin(); // init the mp3 player shield
	if(result != 0) // check result, see readme for error codes.
	{
		Serial.println("couldnt init mp3");
	}
	MP3player.setVolume(0, 0);
	MP3player.setMonoMode(1);
}

void initSD()
{
  //Initialize the SdCard.
	if(!sd.begin(10, SPI_HALF_SPEED))
	{
		Serial.println("couldnt init sd");
		sd.initErrorHalt();
	}
	if(!sd.chdir("/")) 
	{
		Serial.println("couldnt find home dir in sd");
		sd.errorHalt("sd.chdir");
	}
}