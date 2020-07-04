//Brake.h
//Contains logic used to sound the brake cylinders.
//
//	In some trains (R46, R68),
//	Brake cylinders sound based on how much air will be dumped
//	from the beginning notch to the end notch.

//	We'll assume that sound 1 plays for the first half of the 
//	pressure reduction, and sound 2 for the other half.

//  This falls back to the standard air sounds while using dynamic brakes.

#include "streamheader.h"
#include "stdafx.h"

//	format of brake csv file:
//	BcP[0],BcP[1],... (in kPa)


class NYCT_BRAKE
{
private:
	int sound; //current sound playing.
	std::ifstream brakefile;
	std::ofstream test_bpcfile;
	float bcpb, bcpe;
	int bnb, bne;
	
public:
	bool enabled = false;
	int sound1 = ATS_SOUND_STOP;
	int sound2 = ATS_SOUND_STOP;
	NYCT_BRAKE()
	{
		brakefile.open("Brake.csv");
		test_bpcfile.open("C:\\Users\\ben\\bpctest.txt");
		if (!brakefile.is_open()) return;
		enabled = true;

	}

	int RunSound()
	{
		
	}

	void DebugWriteBCP(float bpc, char DllPath[MAX_PATH])
	{
		test_bpcfile << "DLL reads current directory as: " << DllPath << std::endl;
		test_bpcfile << bpc << std::endl;
	}

	void NotchChange()
	{

	}
};