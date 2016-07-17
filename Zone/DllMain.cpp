#include <windows.h>
#include "Settings.h"

extern Settings ZoneSettings;

bool __stdcall DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
	switch(ulReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
			ZoneSettings.SetDllInstance(hModule);

			DisableThreadLibraryCalls(hModule);
		break;
	}

	return true;
}