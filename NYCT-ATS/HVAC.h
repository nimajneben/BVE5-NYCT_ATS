//HVAC.h
//Contains logic used to sound the cooling fan.
#include"streamheader.h"

class NYCT_HVAC {
private:
	int bg_temp;	//ambient temperature
	int rate_frictionbr;	//heating rate when friction brakes are applied (>1)
	int rate_dynamicbr;		//heating rate when dynamic brakes are applied (>1)
	int temperature;	//what the thermistor reads
	std::ifstream tempfile; //temperature file
public:
	bool active;	//HVAC status
	bool InitHVAC() //Init HVAC
	{
		if (!tempfile.open) return false;
		temperature = bg_temp;
		return true;
	}

	void RunHVAC()
	{

	}
};