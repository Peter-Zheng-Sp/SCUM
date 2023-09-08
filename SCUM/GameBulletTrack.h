#pragma once
#include<Windows.h>
#include"Struct.h"
namespace GameBulletTrack
{
	extern ULONG64 BulletTrack_CallAddr;
	extern ULONG64 BulletTrack_JeAddr;
	extern ULONG64 BulletTrack_SpaceAddr;
	extern DWORD BulletTrack_HookData;

	extern ULONG64 MagicBullet_HookAddr;
	extern ULONG64 MagicBullet_SpaceAddr;
	extern ULONG64 MagicBullet_HookData;

	void InitBulletTrack();
	void InitMagicBullet();
	void BulletTrack(bool state, Vector3 Inpawn, Vector3 Enemy);
	void MagicBullet(bool state,Vector3 Enemy);
	void jmp(ULONG64 start, ULONG64 end, BYTE* result);
}