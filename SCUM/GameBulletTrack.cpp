#include "GameBulletTrack.h"
#include"Data.h"
#include"Read.h"

ULONG64 GameBulletTrack::BulletTrack_CallAddr;
ULONG64 GameBulletTrack::BulletTrack_JeAddr;
ULONG64 GameBulletTrack::BulletTrack_SpaceAddr;
DWORD GameBulletTrack::BulletTrack_HookData;

ULONG64 GameBulletTrack::MagicBullet_HookAddr;
ULONG64 GameBulletTrack::MagicBullet_SpaceAddr;
ULONG64 GameBulletTrack::MagicBullet_HookData;

BYTE tmp[8] = {0, 0, 0, 0,  0, 144, 144, 144};

BYTE BulletTrack_ShellCode[] = { 235, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
													83, 72, 131, 236, 32, 72, 139, 5, 223, 255, 255, 255, 72, 133, 
													192, 116, 7, 255, 208, 72, 139, 200, 235, 5, 72, 139, 76, 36, 16, 
													128, 61, 207, 255, 255, 255, 0, 116, 21, 242, 15, 16, 5, 198, 255,
													255, 255, 242, 15, 17, 1, 139, 5, 196, 255, 255, 255, 137, 65, 8, 72, 
													139, 193, 72, 131, 196, 32, 91, 195, 204, 204, 204, 204, 204, 204, 204, 204, 204 };

BYTE MagicBullet_ShellCode[] = { 72, 161, 80, 94, 203, 6, 247, 127, 0, 0, 72, 57, 71, 24, 117, 41, 
													131, 61, 65, 0, 0, 0, 1, 117, 32, 242, 68, 15, 16, 37, 62, 0, 0, 0, 242, 
													68, 15, 17, 167, 208, 1, 0, 0, 139, 13, 55, 0, 0, 0, 137, 143, 216, 1, 0, 
													0, 235, 8, 68, 15, 17, 167, 208, 1, 0, 0, 178, 1, 68, 15, 17, 191, 224, 1, 
													0, 0, 233, 164, 69, 8, 255 };

void GameBulletTrack::jmp(ULONG64 start, ULONG64 end,BYTE* result)
{
	result[0] = 0xE9;
	*(DWORD*)&result[1] = end - start - 5;
}


void GameBulletTrack::InitBulletTrack()
{
	BulletTrack_CallAddr = Data::BaseModule + m_Call;
	BulletTrack_JeAddr= Data::BaseModule + m_Je;
	BulletTrack_SpaceAddr= Data::BaseModule + m_Space;
	BulletTrack_HookData = ReadMem<DWORD>(BulletTrack_CallAddr+1);
	WriteVirtual((LPVOID)BulletTrack_SpaceAddr, BulletTrack_ShellCode, sizeof(BulletTrack_ShellCode));
	WriteMem<ULONG64>(BulletTrack_SpaceAddr + 2, Data::BaseModule+m_code);
}

void GameBulletTrack::InitMagicBullet()
{
	MagicBullet_HookAddr = Data::BaseModule + m_MagicBullet;
	MagicBullet_SpaceAddr = Data::BaseModule + m_Space + 256;
	MagicBullet_HookData = ReadMem<ULONG64>(Data::BaseModule + m_MagicBullet);
	WriteVirtual((LPVOID)(BulletTrack_SpaceAddr+256), MagicBullet_ShellCode, sizeof(MagicBullet_ShellCode));
	//Hook  JmpBack
	BYTE jmpCode[5];
	MagicBullet_SpaceAddr = Data::BaseModule + m_Space + 256;
	jmp(MagicBullet_SpaceAddr + 75, MagicBullet_HookAddr + 18, jmpCode);
	WriteVirtual((LPVOID)(MagicBullet_SpaceAddr + 75), jmpCode, sizeof(jmpCode));
	WriteMem<ULONG64>(MagicBullet_SpaceAddr+2, MagicBullet_SpaceAddr+80);
	WriteMem<DWORD>(MagicBullet_SpaceAddr +88,0);

	jmp(MagicBullet_HookAddr, MagicBullet_SpaceAddr, tmp);
}

void GameBulletTrack::BulletTrack(bool state, Vector3 Inpawn, Vector3 Enemy)
{
	if (state)
	{
		WriteMem<BYTE>(BulletTrack_SpaceAddr + 10, 1); //×·×Ù¿ª¹Ø
		WriteMem<DWORD>(BulletTrack_CallAddr + 1, BulletTrack_SpaceAddr - BulletTrack_CallAddr - 5); // Hook  call ¿Õ°×µØÖ·
		WriteMem<BYTE>(BulletTrack_JeAddr + 1, 133);  //jne
		WriteMem<FLOAT>(BulletTrack_SpaceAddr + 11, (Enemy.x - Inpawn.x) / 1000);
		WriteMem<FLOAT>(BulletTrack_SpaceAddr + 15, (Enemy.y - Inpawn.y) / 1000);
		WriteMem<FLOAT>(BulletTrack_SpaceAddr + 19, (Enemy.z- Inpawn.z) / 1000);
	}
	else
	{
		WriteMem<BYTE>(BulletTrack_SpaceAddr + 10,  0 );
		WriteMem<DWORD>(BulletTrack_CallAddr + 1, BulletTrack_HookData);  //»Ö¸´HookÎ»ÖÃ
		WriteMem<BYTE>(BulletTrack_JeAddr + 1, 132 );  //je
	}
}

void GameBulletTrack::MagicBullet(bool state, Vector3 Enemy)
{
	if (state)
	{
		WriteVirtual((LPVOID)MagicBullet_HookAddr, tmp, sizeof(tmp));
		WriteMem<DWORD>(MagicBullet_SpaceAddr+88, 1);  
		WriteMem<FLOAT>(MagicBullet_SpaceAddr + 96, Enemy.x);
		WriteMem<FLOAT>(MagicBullet_SpaceAddr + 96 + 4, Enemy.y);
		WriteMem<FLOAT>(MagicBullet_SpaceAddr + 96 + 8, Enemy.z);
	}
	else
	{
		WriteMem<DWORD>(MagicBullet_SpaceAddr + 88, 0);
		WriteMem<ULONG64>(MagicBullet_HookAddr, MagicBullet_HookData);
	}
}
