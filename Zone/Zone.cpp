#include <windows.h>
#include <iostream>
#include "Process.h"
#include "Settings.h"

extern Process ZoneProcess;
extern Settings ZoneSettings;

__declspec(dllexport) void _stdcall InstallHook()
{
	ZoneProcess.Initialize();
	ZoneSettings.LoadSettings();

	int patchError = ZoneProcess.PatchCode();

	if(patchError > 0)
	{
		char patchErrorMessage[256];
		sprintf_s(patchErrorMessage, 256, "There was an error patching the Zone.");

		MessageBox(NULL, patchErrorMessage, "Zone", MB_ICONERROR);

		return;
	}

	bool hookError = ZoneProcess.HookAPI();

	if(hookError)
	{
		char hookErrorMessage[256];
		sprintf_s(hookErrorMessage, 256, "There was an error modifying the Zone.");

		MessageBox(NULL, hookErrorMessage, "Zone", MB_ICONERROR);

		return;
	}
}