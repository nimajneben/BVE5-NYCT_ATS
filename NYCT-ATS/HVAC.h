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
	bool enabled;	//Plugin Status
	bool active;	//HVAC status
	NYCT_HVAC() //Init HVAC
	{
		std::ifstream tempfile("Temp.csv");
		if (!tempfile.is_open())
		{
			enabled = false;
			return;
			//TODO: Read temp file and parse into envvars.
		}
		
	}

	void RunHVAC()
	{

	}
};