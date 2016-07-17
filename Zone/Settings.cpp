#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include "Generic.h"
#include "Process.h"
#include "Settings.h"

using namespace std;

extern Process ZoneProcess;

Settings ZoneSettings = Settings();

void Settings::LoadSettings()
{
	LPSTR iniBuffer = CreateBuffer(128);

	char iniPath[MAX_PATH] = {0};
	sprintf_s(iniPath, "%sZone.ini", ZoneProcess.ZoneDirectory);

	GetPrivateProfileString("Startup", "Service", "true", iniBuffer, 128, iniPath);
	SetEnableService(iniBuffer);

	GetPrivateProfileString("General", "RunSpeed", "117", iniBuffer, 128, iniPath);
	SetRunSpeed(iniBuffer);

	GetPrivateProfileString("General", "WalkSpeed", "33", iniBuffer, 128, iniPath);
	SetWalkSpeed(iniBuffer);

	delete[] iniBuffer;
}