#include <Windows.h>
#include "Process.h"
#include "Settings.h"
#include "Include/Detours/Detours.h"
#include "Hooks.h"

extern Settings ZoneSettings;

Process ZoneProcess = Process();

void Process::Initialize()
{
	char* ZonePath = new char[MAX_PATH];
	ZeroMemory(ZonePath, MAX_PATH);

	GetModuleFileNameA(ZoneSettings.GetDllInstance(), ZonePath, MAX_PATH);

	char* ZonePathName = strstr(ZonePath, "Zone.dll");
	strncpy_s(ZonePathName, strlen(ZonePath), "\0\0\0\0\0\0\0\0", strlen(ZonePath));

	ZoneDirectory = ZonePath;
}

bool Process::HookAPI()
{
	bool result = false;

	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if(!ZoneSettings.GetEnableService())
	{
		Hook_ServiceStart = (void(__stdcall*)())(DWORD*)Hook_ServiceStart_Pointer;
		DetourAttach(&(PVOID&)Hook_ServiceStart, ServiceStart);
	}

	Hook_tmfpemfjs = (void(__stdcall*)())(DWORD*)Hook_tmfpemfjs_Pointer;
	DetourAttach(&(PVOID&)Hook_tmfpemfjs, tmfpemfjs);

	Hook_chrlghk = (void(__stdcall*)())(DWORD*)Hook_chrlghk_Pointer;
	DetourAttach(&(PVOID&)Hook_chrlghk, chrlghk);

	Hook_xlrfunction = (void(__stdcall*)())(DWORD*)Hook_xlrfunction_Pointer;
	DetourAttach(&(PVOID&)Hook_xlrfunction, xlrfunction);

	result |= (DetourTransactionCommit() != 0);
	
	return result;
}


int Process::PatchCode()
{
	DWORD imageBase = (DWORD)GetModuleHandle(0);

	PIMAGE_SECTION_HEADER pCodeSection;

	if(!GetSectionHeaderInfo(".text", pCodeSection))
	{
		return PatchCode_Header_Not_Found;
	}

	DWORD baseCodeAddress = imageBase + pCodeSection->VirtualAddress;

	DWORD processId = GetProcessId(GetCurrentProcess());

	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, 0, processId);

	if(!hProcess)
	{
		return PatchCode_Could_Not_Open_Process;
	}

	DWORD lpflOldProtect = 0;

	VirtualProtectEx(hProcess, (DWORD*)baseCodeAddress, pCodeSection->SizeOfRawData, PAGE_EXECUTE_READWRITE, &lpflOldProtect);

	if(!ZoneSettings.GetEnableService())
	{
		BYTE Hook_ServiceStart_Buffer[59] = {0}; // NOP
		memset(Hook_ServiceStart_Buffer, 0x90, sizeof(Hook_ServiceStart_Buffer));

		WriteProcessMemory(hProcess, (LPVOID)Hook_ServiceStart_Pointer, Hook_ServiceStart_Buffer, sizeof(Hook_ServiceStart_Buffer), NULL);

		BYTE Hook_ServiceStart_Loop_Buffer[1] = {
			0xEB
		};

		WriteProcessMemory(hProcess, (LPVOID)Hook_ServiceStart_Loop_Pointer, Hook_ServiceStart_Loop_Buffer, sizeof(Hook_ServiceStart_Loop_Buffer), NULL);
	}

	BYTE Hook_tmfpemfjs_Buffer[50] = {0}; // NOP
	memset(Hook_tmfpemfjs_Buffer, 0x90, sizeof(Hook_tmfpemfjs_Buffer));

	WriteProcessMemory(hProcess, (LPVOID)Hook_tmfpemfjs_Pointer, Hook_tmfpemfjs_Buffer, sizeof(Hook_tmfpemfjs_Buffer), NULL);

	BYTE Hook_chrlghk_Buffer[26] = {0}; // NOP
	memset(Hook_chrlghk_Buffer, 0x90, sizeof(Hook_chrlghk_Buffer));

	WriteProcessMemory(hProcess, (LPVOID)Hook_chrlghk_Pointer, Hook_chrlghk_Buffer, sizeof(Hook_chrlghk_Buffer), NULL);

	BYTE Hook_xlrfunction_Buffer[20] = {0}; // NOP
	memset(Hook_xlrfunction_Buffer, 0x90, sizeof(Hook_xlrfunction_Buffer));

	WriteProcessMemory(hProcess, (LPVOID)Hook_xlrfunction_Pointer, Hook_xlrfunction_Buffer, sizeof(Hook_xlrfunction_Buffer), NULL);

	CloseHandle(hProcess);

	return PatchCode_Success;
}

bool Process::GetSectionHeaderInfo(char* sectionName, PIMAGE_SECTION_HEADER& dest)
{
	const DWORD dwBaseAddress = (DWORD)GetModuleHandle(0);

	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS ntHeader;

	dosHeader = (PIMAGE_DOS_HEADER)dwBaseAddress;
	ntHeader = (PIMAGE_NT_HEADERS)((DWORD)(dosHeader)+(dosHeader->e_lfanew));

	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeader);

	int sectionCount = 0;
	while(sectionCount <= ntHeader->FileHeader.NumberOfSections)
	{
		if(strstr(sectionName, (char*)section->Name))
		{
			dest = section;

			return true;
		}

		section = IMAGE_FIRST_SECTION(ntHeader) + sectionCount;
		sectionCount++;
	}

	return false;
}