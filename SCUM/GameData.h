#pragma once
#include<Windows.h>
#include"Struct.h"
#include"Read.h"
#include"Data.h"
#include"GameAlgorithm.h"
#include <atlstr.h> 
#include<iostream>
using namespace std;
namespace GameData
{
	void GetMatrix(ULONG64 Addr, Matrix* ViewWorld);
	float Get2dDistance(float x1, float y1, float x2, float y2);
	float Get3dDistance(Vector3 MyPos, Vector3 TargerPos, int Divide);
	bool GetPointInCircle(float x, float y, float circleX, float circleY, float r);
	Vector3 ReadVector3(ULONG64 addr, DWORD Type);
	bool WorldToScreen_3D(Matrix viewWorld, Vector3 TargerPos, MRect* result);
	bool WorldToScreen_2D(Matrix viewWorld, Vector3 TargerPos, Vector2* result);
	void GetBonePosition(ULONG64 ObjectMesh, Vector3* resultPos, DWORD BoneId);
	string GetPlayerName(ULONG64 Obj);
	string GetObjectName(ULONG64 Obj);
	int toMove(int a);

	bool isPlayer(string s);
	bool isBoom(string s);
	bool isZombie(string s);
	bool isCar(string s);
	bool isParts(string s);
	bool isWeapon(string s);
	bool isPlane(string s);
	bool isGoods(string s);
	bool isAmmo(string s);
	bool isBox(string s);
}