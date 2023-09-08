#include <Windows.h>
#include <ShlObj.h>
#include <iostream>


#include "Hook.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include"GameMain.h"

ULONG64 ModuleBase;
HMODULE Hooks::hModule;
HWND Hooks::GameHwnd;
WNDPROC Hooks::oWndProc = nullptr;//窗口句柄
ID3D11Device* Hooks::pDevice;
ID3D11DeviceContext* Hooks::pContext;
IDXGISwapChain* Hooks::pSwapChain;

ID3D11Texture2D* Hooks::g_renderTargetTexture;
ID3D11RenderTargetView* Hooks::g_renderTargetView;

tPresent Hooks::Present;
tResize Hooks::Resize;
bool InitializationFirst = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI  Hooks::hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_END)//tuichu
		{
			ExitProcess(0);
		}
			if (wParam == VK_HOME)
		{
			Data::op.isShow = !Data::op.isShow;
		}
	}
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))return true;
	return CallWindowProc(Hooks::oWndProc, hWnd, uMsg, wParam, lParam);
}

bool Hooks::Initialization(HWND game)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = L"DummyWindow";
	if (RegisterClassEx(&wc) == NULL) {
		printf("窗口注册类失败\n");
		return false;
	}
	HWND hWnd = CreateWindowEx(0, wc.lpszClassName, L"", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, wc.hInstance, NULL);
	if (hWnd == NULL) {
		UnregisterClass(L"DummyWindow", wc.hInstance);
		printf("窗口创建失败\n");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	D3D_FEATURE_LEVEL featrueLevel = D3D_FEATURE_LEVEL_11_0;
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featrueLevel, 1, D3D11_SDK_VERSION, &scd, &Hooks::pSwapChain, &Hooks::pDevice, NULL, &Hooks::pContext))) {
		DestroyWindow(hWnd);
		UnregisterClass(L"DummyWindow", wc.hInstance);
		printf("D3D设备初始化失败\n");
		return false;
	}

	DestroyWindow(hWnd);
	UnregisterClass(L"DummyWindow", wc.hInstance);
	return true;
}

void Hooks::OnHook(PVOID* oFunction, PVOID pDetour)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(oFunction, pDetour);
	DetourTransactionCommit();
}
void Hooks::UnHook(PVOID* oFunction, PVOID pDetour, HANDLE newThread)
{
	DetourTransactionBegin();
	if (newThread != 0)
		DetourUpdateThread(newThread);
	else
		DetourUpdateThread(GetCurrentThread());
	DetourDetach(oFunction, pDetour);
	DetourTransactionCommit();
}

HRESULT __stdcall Hooks::hookPresent(IDXGISwapChain* pSwapChain, UINT SyscInterval, UINT Flags)
{
	if (InitializationFirst) {
		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pContext);

		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_renderTargetTexture))) {
			pDevice->CreateRenderTargetView(g_renderTargetTexture, nullptr, &g_renderTargetView);
			g_renderTargetTexture->Release();
		}
		//IMGUI初始化
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		io.DisplaySize.x = ReadMem<DWORD>(Data::BaseModule + m_Screen) ;
		io.DisplaySize.y = ReadMem<DWORD>(Data::BaseModule + m_Screen+4) ;

		//加载字体
		char SystemPath[MAX_PATH] = { 0 };
		char FontPath[MAX_PATH] = { 0 };
		SHGetSpecialFolderPathA(NULL, SystemPath, CSIDL_FONTS, FALSE);
		sprintf_s(FontPath, "%s\\msyh.ttc", SystemPath);
		//io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF(FontPath, 16.f, NULL, io.Fonts->GetGlyphRangesChineseFull());

		//初始化Dx
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);
		ImGui_ImplWin32_Init(sd.OutputWindow);
		ImGui_ImplDX11_Init(pDevice, pContext);
		ImGui_ImplDX11_CreateDeviceObjects();
		ImGui::StyleColorsDark();
		InitializationFirst = false;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//绘制
	GameMain::DrawLoop(); 
	GameMain::DrawMenu(); 	
	GameMain::FuncLoop();

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &g_renderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	return Present(pSwapChain, SyscInterval, Flags);
}

HRESULT __stdcall Hooks::hookResize(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	g_renderTargetView->Release();
	InitializationFirst = true;
	return Resize(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}