class NYCT_ATS2 {
private:
	int mt_timer = 0;	//game time when next ATS beacon passed.
	bool mt_chain = 0;	//timers in sequence
	int mt_type = 0;	//timer type (SG)

public:
	bool ATS_BRAKE;		//tripped?
	float* SPEED_KMH;	//train speed in kmh
	int* TIME;			//time in-game

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

	void TimerPassTS()

	//cancel timer
	void TimerCancel()
	{
		mt_timer = 0;
	}

};