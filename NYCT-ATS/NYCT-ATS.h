//Beacon Indices
#define ATS_TRIP_COCK 0
#define ATS_TIMER_START 1 //Beacon ID for Timer Section Start
#define TRACK_DEAD_START 2 //Beacon to mark start of dead zone
#define TRACK_DEAD_END 3 //Beacon to mark end of dead zone


int EMG_BRAKE; //Brake Notch number corresponding to EMG
int SVC_BRAKE; // Brake Notch number corresponding to Full Service
int BRAKE_NOTCH; // Brake Notch
int POWER_NOTCH; // Power Notch
int REVERSER; // Reverser Position
bool PILOT; // Pilot Lamp
int TIME; // Current Time
float KMH_SPEED; // Speed[km/h]
int deltaT; // FrameRate[ms/frame]

bool DEAD_ZONE; //Dead Zone Simulator

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

	void reset()
	{
		TIMER_CALLTIME = 0;
		TRIPPED = false;
		
	}
	bool TRIPPED = false; //Was the train tripped? We'll initialize to true

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
