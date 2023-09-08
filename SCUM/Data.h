#pragma once
#include<Windows.h>
#include"Struct.h"

const DWORD m_Uworld = 0x5A0A3F0;
const DWORD m_Gname = 0x58B7A80;
const DWORD m_Matrix = 0x5508CB0;
const DWORD m_Screen = 0x5481880;

const DWORD m_ULevel = 0x30;
const DWORD m_Actor = 0x98;
const DWORD m_GameInstance = 0x188;
const DWORD m_LocalPlayer = 0x38;
const DWORD m_PlayerController = 0x30;

const DWORD m_CameraPos = 0x88;
const DWORD m_Mouse = 0x288;

const DWORD m_Inpawn = 0x260;
const DWORD m_Inventory = 0x120;
const DWORD m_RootComponent = 0x130;
const DWORD m_Mesh = 0x280;
const DWORD m_Spin = 0x1C0;
const DWORD m_BoneArray = 0x4A0;
const DWORD m_CharacterMove = 0x288;
const DWORD m_HightJump = 0x150;
const DWORD m_Gost = 0x58;
const DWORD m_Vector3 = 0x1D0;
const DWORD m_ObjectId = 0x18;
const DWORD m_Name = 0xFB8;
const DWORD m_ZombieHp = 0x938;
const DWORD m_UnlimitMake = 0x2485;
const DWORD m_InpawnSpeedSize = 0x98;
const DWORD m_WeaponPtr = 0x1A00;
const DWORD m_WeaponBullet = 0x16DC544;
const DWORD m_WeaponShakeYHook = 0x16F6DE7;
const DWORD m_WeaponShakeXHook = 0x16F6E36;
const DWORD m_ThroughWallHook = 0x2F55037;

const DWORD m_ObjectRealNameOne = 0x3A0;
const DWORD m_ObjectRealNameTwo = 0x8;


//BulletTrack
const DWORD m_Call = 0x16DE6D3;
const DWORD m_Je = 0x16DE720;
const  DWORD m_Space = 0x401264C;
const DWORD m_code = 0xF91BF0;
const DWORD m_MagicBullet = 0x301884F;


const DWORD m_CameraManager = 0x2B8;
const DWORD m_CanSee = 0x260;

//41 8D 46 01 89 43 08 3B 43 0C 7E 0B 41 8B D6 48 8B CB E8 ?? ?? ?? ?? 48 8B 0B 48 8B 86 F8 00 00 00 4A 89 04 F1 49 83 C7 08 49 FF C4
//SCUM.exe+2BF9A7E - 48 8B 0B              - mov rcx,[rbx]    {rbx}
const DWORD m_GameTime = 0x59FD1D8;
const DWORD m_offsetOne = 0x18;
const DWORD m_offsetTwo = 0x20;
const DWORD m_offsetThree = 0x238;

//Unlock
const DWORD m_UnLock = 0x14457A6;






namespace Data
{
	extern ULONG64 BaseModule;
	extern HWND hGame;
	extern DWORD dwSightX;
	extern DWORD dwSightY;
	extern UE4Engine<ULONG64> g_Ue4Engine;
	extern Object<ULONG64> g_LocalPlayer;
	extern ObjArray g_ObjArray;
	extern BOOL isGameMenu;
	extern DWORD MagicBulletValue;
	extern Option op;
	extern AimBot aimBot[2];
}
