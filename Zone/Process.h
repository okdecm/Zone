#pragma once

#include <windows.h>

#define PatchCode_Success					0;
#define PatchCode_Header_Not_Found			1;
#define PatchCode_Could_Not_Open_Process	2;

class Process
{
	public:
		char* ZoneDirectory;

		void Initialize();

		int PatchCode();
		bool HookAPI();

		bool GetSectionHeaderInfo(char* sectionName, PIMAGE_SECTION_HEADER& dest);
};