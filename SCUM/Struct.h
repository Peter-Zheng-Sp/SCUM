#pragma once
#include<Windows.h>
#include<d3dx9math.h>
#include<string>
#include<vector>
#include"ImGui\imgui.h"
typedef  D3DXVECTOR4 Vector4;
typedef  D3DXVECTOR3 Vector3;
typedef  D3DXVECTOR2 Vector2;
typedef  D3DMATRIX     Matrix;

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

typedef struct TRect
{
	int x;
	int y;
	int w;
	int h;
}MRect;


struct FTransform
{
	Vector4 Rotation;
	Vector3 Translation;
	Vector3 Scale3D;
};

template <class T>
struct UE4Engine
{
	T pGname;
	T pMatrix;
	T pUworld;
	T pUlevel;
	T ActorArray;
	DWORD ActorCount;
	T GameInstance;
	T LocalPlayer;
	T PlayerController;
	Matrix ViewWorld;
	T CameraPos;
	T MouseAddr;
	T ScreenAddr;
};

template <class T>
struct Object
{
	T Object;
	DWORD ObjectId;
	std::string  ObjectType;
	std::string  ObjectRealName;
	FLOAT ObjectHp;
	std::string ObjectName;
	T RootComponent;
	T Mesh;
	T WeaponPtr;
	Vector3 Vector3d;
	Vector3 Velocity;
	FLOAT Distance;
};


struct ObjArray
{
	std::vector<ULONG64> player;
	std::vector<ULONG64> zombie;
	std::vector<ULONG64> car;
	std::vector<ULONG64> boom;
	std::vector<ULONG64> box;
	std::vector<ULONG64> parts;
	std::vector<ULONG64> other;
	std::vector<ULONG64> plane;
	std::vector<ULONG64> weapon;
	std::vector<ULONG64> goods;
	std::vector<ULONG64> ammo;
};




typedef struct TOPTION
{
	bool isShow;
	//Esp
	
	bool playerBox;
	bool playerInfo;
	bool zombieBox;
	bool zombieInfo;
	bool plane;
	bool car;
	bool goods;
	bool parts;
	bool weapon;
	bool ammo;
	bool box;
	bool boom;
	bool crosshare;
	bool playerbone;
	bool zombiebone;
	//aim
	int aimType; //0无 1弹道 2魔术 3右键自瞄
	int aimPart;
	bool showScope;
	float aimSpeed;
	float aimScope;

	//super
	bool superSpeed;
	float speedSize;
	bool gatherPlayer;
	bool gatherZombie;
	bool noCollision;
	bool hightJump;
	float jumpSize;
	bool noRecoil;
	bool unlimitBullet;
	bool noMakeCondic;
	bool gost;
	bool unlimitMake;
	bool noNight;
	bool unLock;
	bool carSky;
	bool carSpeed;
	float carSpeedSize;
}Option;


typedef struct TAimBot
{
	bool bLook;
	ULONG64 dwObj;
	ULONG64 dwObjMesh;
	Vector3 Position;
	FLOAT Value1;
	FLOAT Value2;
}AimBot;