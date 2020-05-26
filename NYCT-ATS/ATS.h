#include<array>

int speedo_kmh_to_mph(float& kmh) {
	int result = floor(fabs(0.6213711922 * kmh));
	if (result > 99) result = 99;
	return result;
}; //KMH -> MPH and floor.

class NYCT_ATS2 {
private:

	//one-shot variables
	int mt_timer = 0;	//game time when next ATS beacon passed.
	bool mt_chain = 0;	//timers in sequence
	int mt_type = 0;	//timer type (SG(T))

	//two-shot variables
	std::array<std::array<int, 2>, 3> mt2_timer = { {0,0} };	//n shot, then n timer.
	std::array<bool, 3> mt2_en = { 0,0,0 };		//n timer, shot suceeded


public:
	bool ATS_BRAKE;		//tripped?
	float* SPEED_KMH;	//train speed in kmh
	int* TIME;			//time in-game
	int HUD_DISPLAY = 99;	//hud display


	void RunAts()
	{

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
		switch (beacontype)
		{
			int i = (beacontype % 3);	//selector.
		case 21:
		case 24:
		case 27:	//start s timing
			mt2_timer[i][0] = *TIME;
			mt2_en[i] = false;
			break;
		case 22:
		case 25:
		case 28:	//after s timing
			if (!mt2_en[i])
				mt2_timer[i][1] = *TIME;
			break;
		case 23:
		case 26:
		case 29:	//after timing signal
			if (!mt2_en[i] && mt2_timer[i][1] + timer < *TIME)
				ATS_BRAKE == true;
			break;

		}
	}

	//cancel timer
	void TimerCancel()
	{
		mt_timer = 0;
		mt2_timer.fill({ 0,0,0 });
	}

	void TimerDisableOS()
	{
		mt_timer = 0;
	}

	void TimerDisableTS(int beacontype)
	{
		mt2_en[beacontype % 3] = true;
	}
};

class NYCT_ATS_HUD
{
private:
	int block_aspect; //what the block aspect should be.

};