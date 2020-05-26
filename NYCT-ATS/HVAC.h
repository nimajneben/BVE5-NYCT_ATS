//HVAC.h
//Contains logic used to sound the cooling fan.
#include<iostream>
#include<fstream>

std::ifstream tempfile("temp.txt"); //temperature file

class NYCT_HVAC {
private:
	int bg_temp;	//ambient temperature
	int rate_frictionbr;	//heating rate when friction brakes are applied (>1)
	int rate_dynamicbr;		//heating rate when dynamic brakes are applied (>1)
	int temperature;	//what the thermistor reads
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