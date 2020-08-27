// NYCT-ATS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "atsplugin.h"
#include "NYCT-ATS.h"
#include "ATS.h"
#include "CBTC.h"

NYCT_ATS2 ATS_PLUGIN;
NYCT_CBTC CBTC_PLUGIN;

int MPH_SPEED;

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
	CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_STOP;
}

ATS_API void WINAPI Load()
{
	KMH_SPEED = 0;
	ATS_PLUGIN.reset();
	CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_STOP;
}

ATS_API void WINAPI Dispose()
{
	KMH_SPEED = 0;
	ATS_PLUGIN.reset();
}

//Game calls this every frame.
ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehiclestate, int *panel, int *sound)
{
	//kmh to mph conversion
	KMH_SPEED = vehiclestate.Speed;
	TIME = vehiclestate.Time;
	MPH_SPEED = speedo_kmh_to_mph(KMH_SPEED);
	panel[0] = MPH_SPEED % 10; //Ones digit
	panel[1] = MPH_SPEED / 10; //Tens digit
	//panel[2] = 

	if (panel[1] == 0) panel[1] = 10; 

	//check tripped status
	if (ATS_PLUGIN.TRIPPED || CBTC_PLUGIN.TRIPPED) 
		HANDLE_OUTPUT.Brake = EMG_BRAKE;
	else 
		HANDLE_OUTPUT.Brake = BRAKE_NOTCH;

	//power cut if doors open.
	if 
		(PILOT == false)	HANDLE_OUTPUT.Power = 0;
	else 
		HANDLE_OUTPUT.Power = POWER_NOTCH;

	HANDLE_OUTPUT.Reverser = REVERSER;

	//cbtc:
	panel[101] = MPH_SPEED; //Both digits
	panel[102] = (MPH_SPEED % 10) + (10 * (MPH_SPEED > 9)); //1-10mph LSB
	panel[103] = (MPH_SPEED % 10) + (10 * (MPH_SPEED < 10)); //>10mph LSB
	panel[104] = (MPH_SPEED / 10) + (10 * (MPH_SPEED < 10)); //>10mph MSB
	panel[110] = CBTC_PLUGIN.YELLOW_LIMIT;
	panel[111] = CBTC_PLUGIN.RED_LIMIT;
	panel[112] = !CBTC_PLUGIN.YELLOW_ALARM;
	panel[113] = !CBTC_PLUGIN.RED_ALARM;

	sound[101] = CBTC_PLUGIN.YELLOW_ALARM;

	if ((int)(KMH_SPEED * 10 )> CBTC_PLUGIN.YELLOW_LIMIT)
	{
		CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_STOP;
	}


	//misc: reserved for HVAC.
	//sound[201]
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
		if (KMH_SPEED > 5 && (beaconData.Signal == 0 || ATS_PLUGIN.timer_check_failed(TIME)) ) //Checking for RED Signal and if we're going too fast.
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

//Game calls this when an ATS key was pressed.
ATS_API void WINAPI KeyDown(int atsKeyCode)
{
	//CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_PLAYLOOPING;
}

//Game calls this when an ATS key was released.
ATS_API void WINAPI KeyUp(int atsKeyCode)
{
	//if (atsKeyCode == ATS_KEY_S) //space
	//{
	//	CBTC_PLUGIN.YELLOW_ALARM = ATS_SOUND_STOP;
	//}
}