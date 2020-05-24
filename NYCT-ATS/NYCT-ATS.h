//Beacon Indices
#define ATS_TRIP_COCK 0
#define ATS_TIMER_START 1 //Beacon ID for Timer Section Start


int EMG_BRAKE; //Brake Notch number corresponding to EMG
int SVC_BRAKE; // Brake Notch number corresponding to Full Service
int BRAKE_NOTCH; // Brake Notch
int POWER_NOTCH; // Power Notch
int REVERSER; // Reverser Position
bool PILOT; // Pilot Lamp
int TIME; // Current Time
float KMH_SPEED; // Speed[km/h]
int deltaT; // FrameRate[ms/frame]

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
ATS_HANDLES HANDLE_OUTPUT; //Handle Output

//KMH -> MPH, floor, and bounds check to 99 mph.
int speedo_kmh_to_mph(float &kmh) { 
	int result = floor(fabs(0.6213711922 * kmh));
	if (result > 99) result = 99;
	return result;
	}; //KMH -> MPH and floor.

class NYCT_ATS
{
private:
	int TIMER_CALLTIME; //Store gametime a timer was called.
	int TIMER_TIMELENGTH; //Store how long to time.
	
	 
public:
<<<<<<< Updated upstream
	bool TRIPPED = false;
=======
	bool TRIPPED = false; //Was the train tripped?
>>>>>>> Stashed changes
	void reset()
	{
		TIMER_CALLTIME = 0;
		TRIPPED = false;
		
	}

	void begin_timer(int current_time, int timerlength)
	{
		TIMER_CALLTIME = current_time;
		TIMER_TIMELENGTH = timerlength;
	}

	bool timer_check_failed(int current_time)
	{
		return (current_time - TIMER_CALLTIME < TIMER_TIMELENGTH);
	}

};
<<<<<<< Updated upstream
=======

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

	int startATO(int &speed)
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

	int accelATO(int &speed)
	{

	}

	void playYellowChime()
	{
		if (YELLOW_ALARM == 1);
	}
};
>>>>>>> Stashed changes
