#pragma once
#include <d3d11.h>

#include "Detours/detours.h"
#pragma comment(lib,"Detours/detours.lib")


extern ULONG64 ModuleBase;
typedef HRESULT(__stdcall* tPresent)(IDXGISwapChain* pSwapChain, UINT SyscInterval, UINT Flags);
typedef HRESULT(__stdcall* tResize)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
namespace Hooks {
	extern HWND GameHwnd;
	extern HMODULE hModule;
	extern WNDPROC oWndProc;
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	extern IDXGISwapChain* pSwapChain;

	extern ID3D11Texture2D* g_renderTargetTexture;
	extern ID3D11RenderTargetView* g_renderTargetView;

	extern tPresent Present;
	extern tResize Resize;

	LRESULT WINAPI  hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT __stdcall hookPresent(IDXGISwapChain* pSwapChain, UINT SyscInterval, UINT Flags);
	HRESULT __stdcall hookResize(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	bool Initialization(HWND game);
	void OnHook(PVOID* oFunction, PVOID pDetour);
	void UnHook(PVOID* oFunction, PVOID pDetour, HANDLE newThread = 0);
}
