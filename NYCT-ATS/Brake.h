//Brake.h
//Contains logic used to sound the brake cylinders.
//
//	In some trains (R46, R68),
//	Brake cylinders sound based on how much air will be dumped
//	from the beginning notch to the end notch.

//	We'll assume that sound 1 plays for the first half of the 
//	pressure reduction, and sound 2 for the other half.

#include "streamheader.h"
#include "stdafx.h"

//	format of brake csv file:
//	BrakeNotch,BCPressure


class NYCT_BRAKE
{
private:
	int sound; //current sound playing.
	std::ifstream brakefile;

public:
	bool enabled = false;
	NYCT_BRAKE()
	{
		std::ifstream brakefile("Brake.csv");
		if brakefile.is_open() enabled = true;
	}

	int PlaySound()
	{
		r
	}

};