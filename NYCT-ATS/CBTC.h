class NYCT_CBTC
{
public:
	//variables:
	//Speed Enforcement
	int YELLOW_LIMIT = 500; //warning speed limit (kmh * 10).
	int RED_LIMIT = 950; //emg brake speed limit (kmh * 10).
	bool YELLOW_ALARM; //ATO: Alerter and sound. ATP: circle screen and sound
	bool RED_ALARM; //ATPM: Solid red circle.
	bool TRIPPED = false;

	//Block Enforcement
	int RED_DISTANCE; //we're cleared till what distance?


	//Overrun Protection (ORP)


	//Total Enforcement





	//functions
	void initATPM()
	{
		/*TODO:
		  1) Update mode icon to ATPM
		  2) Initalize variables.
		*/
	}

	void initATO()
	{
		/*
		  1) Update mode icon to ATO
		  2) Initalize variables.
		*/
	}

	int startATO(int& speed)
	{
		/*
		If SPEED < YELLOW_LIMIT, accelerate
			< 10 kmh to limit, 50% throttle
			< 5 kmh to limit, coast.

		If SPEED >= YELLOW_LIMIT, brake


		*/

		if (speed - YELLOW_LIMIT < -10) return 3;
		else if (speed - YELLOW_LIMIT < -5) return 1;
		else return 0;
	}

	int accelATO(int& speed)
	{

	}

	void playYellowChime()
	{
		if (YELLOW_ALARM == 1);
	}
};