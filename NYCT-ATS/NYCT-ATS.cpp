// NYCT-ATS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "atsplugin.h"
#include "NYCT-ATS.h"

NYCT_ATS ATS_PLUGIN;

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//Initialize variables here with pointers to actual ingame stuff
		
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


// Game requests plugin version
ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

//Game provides vehicle data
ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	SVC_BRAKE = vehicleSpec.BrakeNotches;
	EMG_BRAKE = SVC_BRAKE + 1;
}

//Game scenario is started
ATS_API void WINAPI Initialize(int brake)
{
	KMH_SPEED = 0;
	ATS_PLUGIN.reset();
}

//Game calls this every frame.
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehiclestate, int *panel, int *sound)
{
	
	KMH_SPEED = vehiclestate.Speed;
	TIME = vehiclestate.Time;
	panel[0] = speedo_kmh_to_mph(KMH_SPEED) % 10; //Ones digit of speedo
	panel[1] = speedo_kmh_to_mph(KMH_SPEED) / 10; //Tens digit of speedo

	if (ATS_PLUGIN.TRIPPED == true)
	{
		HANDLE_OUTPUT.Brake = EMG_BRAKE;
	}
	else
	{
		HANDLE_OUTPUT.Brake = BRAKE_NOTCH;
	}

	if (PILOT == false)
	{
		HANDLE_OUTPUT.Power = 0;
	}
	else
	{
		HANDLE_OUTPUT.Power = POWER_NOTCH;
	}

	HANDLE_OUTPUT.Reverser = REVERSER;
	return HANDLE_OUTPUT;
}


//Game calls this when train passes a beacon
ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData) {
	switch (beaconData.Type)
	{
	case ATS_TIMER_START:
		ATS_PLUGIN.begin_timer(TIME, beaconData.Optional);
		break;
	case ATS_TRIP_COCK:
		if (KMH_SPEED > 5 && (beaconData.Signal == 0 || ATS_PLUGIN.timer_check_failed(TIME)) ) //Checking for RED Signal and we're going too fast.
		{
			ATS_PLUGIN.TRIPPED = true;
		}
	}
}

//Game calls this when doors are closed.
ATS_API void WINAPI DoorClose()
{
	PILOT = true;
}

//Game calls this when doors are opened.
ATS_API void WINAPI DoorOpen()
{
	PILOT = false;
}

//Game calls this when the brake notch is changed.
ATS_API void WINAPI SetBrake(int notch)
{
	BRAKE_NOTCH = notch;
}

//Game calls this when the master controller is changed.
ATS_API void WINAPI SetPower(int notch)
{
	POWER_NOTCH = notch;
}

//Game calls this when the reverser is changed.
ATS_API void WINAPI SetReverser(int pos)
{
	REVERSER = pos;
}