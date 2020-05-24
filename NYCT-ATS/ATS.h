#include<array>
class NYCT_ATS2 {
private:

	//one-shot varables
	int mt_timer = 0;	//game time when next ATS beacon passed.
	bool mt_chain = 0;	//timers in sequence
	int mt_type = 0;	//timer type (SG(T))

	//two-shot variables
	std::array<std::array<int, 2>, 2> mt2_timer = {0,0,0,0};	//n shot, then n timer.
	std::array<bool, 2> mt2_timerpass = { 0,0 };		//n timer, shot suceeded


public:
	bool ATS_BRAKE;		//tripped?
	float* SPEED_KMH;	//train speed in kmh
	int* TIME;			//time in-game

	void RunAts()
	{
		if (mt_timer)
	}

	//passed key-byable signal
	//signal: state
	void PassAutoAppr(int signal)
	{
		if (signal == 1 && *SPEED_KMH > 5.0) ATS_BRAKE = true;
	}
	
	//passed no-key-by signal
	//signal: state
	void PassHome(int signal)
	{
		if (signal <= 1) ATS_BRAKE = true;;
	}

	//passed one-shot timer
	void TimerPassOS(int timer)
	{
		if (mt_timer && *TIME < mt_timer)
		{
			ATS_BRAKE = true; mt_timer = 0;

		}

		if (timer) mt_timer = *TIME + timer;
		else mt_timer = 0;
	}

	void TimerPassTS(int beacontype, int timer)
	{
		switch(beacontype)
			case 11:
				if (!mt2_timer[0][0])
				{
					mt2_timer[0][0] = *TIME;
					mt2_timerpass[0][0] = false;
				}
				else
				{
					mt2_timer[1][0] = *TIME;
					mt2_timerpass[1][0] = false;
				}
				break;
			case 12:
				if (!mt2_timer[0][0])
				{
					mt2_timer[0][1] = *TIME;
				}
	}

	//cancel timer
	void TimerCancel()
	{
		mt_timer = 0;
	}

};