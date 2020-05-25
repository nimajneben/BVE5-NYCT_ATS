//HVAC.h
//Contains logic used to sound the cooling fan.
#include<iostream>
#include<fstream>

std::ifstream tempfile("temp.txt"); //temperature file

class NYCT_HVAC {
public:
	int NYCT_HVAC()
	{
		if (!tempfile.open)
			std::cout << "Cannot open temperature file!";
	}
};