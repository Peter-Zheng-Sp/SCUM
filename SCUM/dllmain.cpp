// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include<Windows.h>
#include"Thread.h"

HANDLE curThread;
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CHAR modulePtah[MAX_PATH];
        CHAR exeName[MAX_PATH];
        GetModuleFileNameA(NULL, modulePtah, MAX_PATH);
        strcat(modulePtah, " -> Inject OK!");
        strcpy(exeName, modulePtah);
        if (strstr(exeName, "SCUM.exe") == 0)
        {
            return 0;
        }
        //MessageBoxA(NULL, modulePtah, "Info", MB_ICONINFORMATION);
        MessageBoxA(NULL, "游戏界面按下Home键激活辅助", "Info", MB_ICONINFORMATION);
        HANDLE Data1 = Thread::MyCreateThread((LPTHREAD_START_ROUTINE)Thread::InitThread, NULL, NULL);
        if (Data1 != NULL)
            CloseHandle(Data1);
        break;
    }
    return TRUE;
}


