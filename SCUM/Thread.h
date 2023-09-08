#pragma once
#include<Windows.h>
#include"Hook.h"
#include"Data.h"
#include<fstream>
#include"GameData.h"
#include"GameBulletTrack.h"

typedef struct
{
	DWORD64 dwEP;
	void* pParam;
}CALL_MYFUNCTION, * PCALL_MYFUNCTION;

typedef DWORD(*_Function)(VOID* p);

namespace Thread
{
	DWORD GetModuleSize(DWORD64 base);
	void WINAPI MyFunctionThread(PCALL_MYFUNCTION pCMF);
	HANDLE MyCreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, LPDWORD lpThreadId);
	DWORD  InitThread();
}
