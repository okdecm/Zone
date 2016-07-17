#pragma once

#include <windows.h>

extern const DWORD Hook_ServiceStart_Pointer;
extern const DWORD Hook_ServiceStart_Loop_Pointer;
extern const DWORD Hook_tmfpemfjs_Pointer;
extern const DWORD Hook_chrlghk_Pointer;
extern const DWORD Hook_xlrfunction_Pointer;

extern void(__stdcall *Hook_ServiceStart)();
extern void ServiceStart();

extern void(__stdcall *Hook_tmfpemfjs)();
extern void tmfpemfjs();

extern void(__stdcall *Hook_chrlghk)();
extern void chrlghk();

extern void(__stdcall *Hook_xlrfunction)();
extern void xlrfunction();