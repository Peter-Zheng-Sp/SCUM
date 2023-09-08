#include"Thread.h"
#include"GameMain.h"

//
// 获取模块大小
//
DWORD Thread::GetModuleSize(DWORD64 base)
{
    IMAGE_DOS_HEADER dos_header = { 0 };
    IMAGE_NT_HEADERS nt_headers = { 0 };
    if (!base)return -1;
    dos_header = *(IMAGE_DOS_HEADER*)base;
    nt_headers = *(IMAGE_NT_HEADERS*)(base + dos_header.e_lfanew);
    return nt_headers.OptionalHeader.SizeOfImage;
}


//
//创建线程
//
void WINAPI Thread::MyFunctionThread(PCALL_MYFUNCTION pCMP)
{
    if (pCMP != NULL && pCMP->dwEP != NULL)
    {
        _Function Function = (_Function)pCMP->dwEP;
        Function(pCMP->pParam);
    }
}


HANDLE Thread::MyCreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, LPDWORD lpThreadID)
{
    HANDLE hNtDll = GetModuleHandleA("ntdll.dll");
    if (hNtDll != NULL)
    {
        DWORD dwImageSize = GetModuleSize((DWORD64)hNtDll);
        BYTE* pMemoryData = (BYTE*)hNtDll + dwImageSize - 0x400;
        if (pMemoryData != NULL)
        {
            DWORD dwProtect;
            VirtualProtect(pMemoryData, 0x100, PAGE_EXECUTE_READWRITE, &dwProtect);
            CALL_MYFUNCTION* pCMP = (CALL_MYFUNCTION*)VirtualAlloc(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
            pCMP->dwEP = (DWORD64)(lpStartAddress);
            pCMP->pParam = lpParameter;
            memcpy((LPVOID)pMemoryData, (LPVOID)MyFunctionThread, 0x100);
            HANDLE hHandle = CreateRemoteThread(GetCurrentProcess(), NULL, 0, (LPTHREAD_START_ROUTINE)pMemoryData, pCMP, NULL, lpThreadID);
            return hHandle;
        }
    }
    return 0;
}

//
//主线程
//
DWORD  Thread::InitThread()
{
    //AllocConsole();
    //FILE* stream;
    //freopen_s(&stream, "CON", "w", stdout);
    //SetConsoleTitle(L"SCUM 内部绘制 Hook ");
    while (true)
    {
        if (GetAsyncKeyState(VK_HOME) != 0)
            break;
    }
    Data::hGame = FindWindow(L"UnrealWindow", L"SCUM  ");
    Data::op.isShow = true;
    Data::op.aimScope = 50;
    Data::op.aimSpeed = 1;
    Data::op.jumpSize = 1;
    Data::op.speedSize = 1;
    Data::op.carSpeedSize = 100;
    /*#########################开始Hook################################################################*/
    Hooks::GameHwnd = Data::hGame;
    Data::BaseModule = (ULONG64)GetModuleHandleA("SCUM.exe");
    GameBulletTrack::InitBulletTrack(); //初始化子弹追踪
    GameBulletTrack::InitMagicBullet();//初始化魔术子弹
    Hooks::oWndProc = (WNDPROC)SetWindowLongPtr(Hooks::GameHwnd, -4, (DWORD_PTR)Hooks::hkWndProc);
    CloseHandle(Thread::MyCreateThread((LPTHREAD_START_ROUTINE)GameMain::DataLoop, NULL, NULL));
    if (Hooks::oWndProc == nullptr) return 0;
    //------------------------------------------------------------------------------------------------------------------
    if (Hooks::Initialization(Data::hGame)) {

        DWORD_PTR* pSwapChainVT = reinterpret_cast<DWORD_PTR*>(reinterpret_cast<DWORD_PTR*>(Hooks::pSwapChain)[0]);
        Hooks::Present = reinterpret_cast<tPresent>(pSwapChainVT[8]);
        Hooks::Resize = reinterpret_cast<tResize>(pSwapChainVT[13]);
        //--------------------------------------------------------------------------------------------------------------
        Hooks::OnHook(reinterpret_cast<PVOID*>(&Hooks::Present), (PVOID)Hooks::hookPresent);
        Hooks::OnHook(reinterpret_cast<PVOID*>(&Hooks::Resize), (PVOID)Hooks::hookResize);
        //--------------------------------------------------------------------------------------------------------------
        Hooks::pDevice->Release();
        Hooks::pContext->Release();
        Hooks::pSwapChain->Release();
    }
    return 0;
}