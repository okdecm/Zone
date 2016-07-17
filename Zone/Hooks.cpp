#include <windows.h>
#include "Hooks.h"
#include "Settings.h"
#include "Process.h"

extern Settings ZoneSettings;
extern Process ZoneProcess;

extern const DWORD Hook_ServiceStart_Pointer = 0x576F6E;
extern const DWORD Hook_ServiceStart_Loop_Pointer = 0x5762CD;
extern const DWORD Hook_tmfpemfjs_Pointer = 0x57DC84;
extern const DWORD Hook_chrlghk_Pointer = 0x575B32;
extern const DWORD Hook_xlrfunction_Pointer = 0x577C28;

void(__stdcall *Hook_ServiceStart)();
void _declspec(naked) ServiceStart()
{
	DWORD z_OnServiceStartPointer;
	z_OnServiceStartPointer = 0x48AB60;

	__asm
	{
		mov		ecx, esp
		mov		dword ptr [esp+0x28], esp
		call	z_OnServiceStartPointer
		jmp		Hook_ServiceStart
	}
}

void(__stdcall *Hook_tmfpemfjs)();
void _declspec(naked) tmfpemfjs()
{
	DWORD z_StartSkyPointer;
	z_StartSkyPointer = 0x578F40;
	DWORD z_StartEarthPointer;
	z_StartEarthPointer = 0x578390;
	DWORD z_StartBlackPointer;
	z_StartBlackPointer = 0x578330;
	DWORD z_StartYellowPointer;
	z_StartYellowPointer = 0x578EC0;
	DWORD z_StartHomePointer;
	z_StartHomePointer = 0x578740;
	DWORD z_StartHousePointer;
	z_StartHousePointer = 0x580B60;
	DWORD z_StartWidePointer;
	z_StartWidePointer = 0x5783C0;
	DWORD z_StartToughPointer;
	z_StartToughPointer = 0x57B0B0;
	DWORD z_StartSunPointer;
	z_StartSunPointer = 0x578650;
	DWORD z_StartMoonPointer;
	z_StartMoonPointer = 0x578C30;
	DWORD z_StartFullPointer;
	z_StartFullPointer = 0x580C00;
	DWORD z_StartSinkPointer;
	z_StartSinkPointer = 0x579680;
	DWORD z_StartStarPointer;
	z_StartStarPointer = 0x5789E0;
	DWORD z_StartSleepPointer;
	z_StartSleepPointer = 0x582480;
	DWORD z_StartOpenPointer;
	z_StartOpenPointer = 0x580CA0;
	DWORD z_StartLongPointer;
	z_StartLongPointer = 0x5823D0;
	DWORD z_RunSpeedPointer;
	z_RunSpeedPointer = 0xD792600;
	DWORD z_WalkSpeedPointer;
	z_WalkSpeedPointer = 0xD792604;

	int runSpeed;
	runSpeed = ZoneSettings.GetRunSpeed();
	int walkSpeed;
	walkSpeed = ZoneSettings.GetWalkSpeed();

	__asm
	{
		call	z_StartSkyPointer		// zs_start_sky
		call	z_StartEarthPointer		// zs_start_earth
		call	z_StartBlackPointer		// zs_start_black
		call	z_StartYellowPointer	// zs_start_yellow
		call	z_StartHomePointer		// zs_start_home
		call	z_StartHousePointer		// zs_start_house
		call	z_StartWidePointer		// zs_start_wide
		call	z_StartToughPointer		// zs_start_tough
		call	z_StartSunPointer		// zs_start_sun
		call	z_StartMoonPointer		// zs_start_moon
		call	z_StartFullPointer		// zs_start_full
		call	z_StartSinkPointer		// zs_start_sink
		call	z_StartStarPointer		// zs_start_star
		call	z_StartSleepPointer		// zs_start_sleep
		call	z_StartOpenPointer		// zs_start_open
		call	z_StartLongPointer		// zs_start_long
		push	eax
		push	edx
		mov		eax, z_RunSpeedPointer
		mov		edx, runSpeed			// runSpeed
		mov		dword ptr [eax], edx
		mov		eax, z_WalkSpeedPointer
		mov		edx, walkSpeed			// walkSpeed
		mov		dword ptr [eax], edx
		pop		edx
		pop		eax
		jmp		Hook_tmfpemfjs
	}
}

void(__stdcall *Hook_chrlghk)();
void _declspec(naked) chrlghk()
{
	DWORD z_ServiceIOCP;
	z_ServiceIOCP = 0x576320;
	DWORD z_ServiceMainThread;
	z_ServiceMainThread	= 0x577E10;
	DWORD z_ServiceAcceptor;
	z_ServiceAcceptor = 0x5762E0;
	DWORD z_StartStackChecker;
	z_StartStackChecker = 0x576FE0;

	DWORD z_ESIHoldPointer;
	z_ESIHoldPointer = 0x130E3DA8;

	__asm
	{
		push	eax
		mov		eax, z_ESIHoldPointer
		mov		dword ptr [eax], esi
		pop		eax
		call	z_ServiceIOCP
		call	z_ServiceMainThread
		call	z_ServiceAcceptor
		call	z_StartStackChecker
		mov		eax, 1
		jmp		Hook_chrlghk
	}
}

void(__stdcall *Hook_xlrfunction)();
void _declspec(naked) xlrfunction()
{
	__asm
	{
		mov		eax, 1
		jmp		Hook_xlrfunction
	}
}