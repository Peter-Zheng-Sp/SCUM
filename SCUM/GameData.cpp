#include"GameData.h"
#include"xorstr.hpp"
#include<stdlib.h>

int GameData::toMove(int a)
{
	a = fabs(a);
	if (a > 200)
		return 50;
	else if (a > 100)
		return 25;
	else if (a > 80)
		return 25;
	else if (a > 60)
		return 20;
	else if (a > 45)
		return 15;
	else if (a > 20)
		return 5;
	else if (a > 9)
		return 3;
	else if (a > 3)
		return 1;
	return 0;
}

void GameData::GetMatrix(ULONG64 Addr, Matrix* ViewWorld)
{
	*ViewWorld = ReadMem<Matrix>(ReadMem<ULONG64>(ReadMem<ULONG64>(Addr) + 0x20) + 0x270);
}

float GameData::Get2dDistance(float x1, float y1, float x2, float y2)
{
	float dDistance;
	x1 = x1 - x2;
	y1 = y1 - y2;
	dDistance = sqrt(x1 * x1 + y1 * y1);
	return dDistance;
}

float GameData::Get3dDistance(Vector3 MyPos, Vector3 TargerPos, int Divide)
{
	float fDistance;
	Vector3 vec;
	vec.x = TargerPos.x - MyPos.x;
	vec.y = TargerPos.y - MyPos.y;
	vec.z = TargerPos.z - MyPos.z;
	fDistance = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return fDistance / Divide;
}

bool GameData::GetPointInCircle(float x, float y, float circleX, float circleY, float r)
{
	float fDistance;
	fDistance = sqrt(pow(x - circleX, 2) + pow(y - circleY, 2));
	if (fDistance <= r)
		return true;
	return false;
}

Vector3 GameData::ReadVector3(ULONG64 addr, DWORD Type)
{
	return ReadMem<Vector3>(addr + Type);
}

bool GameData::WorldToScreen_3D(Matrix viewWorld, Vector3 TargerPos, MRect* result)
{
	float fViewW = viewWorld._14 * TargerPos.x + viewWorld._24 * TargerPos.y + viewWorld._34 * TargerPos.z + viewWorld._44;
	if (fViewW < 0.01f) { return false; }
	fViewW = 1 / fViewW;
	float fBoxX = Data::dwSightX + (viewWorld._11 * TargerPos.x + viewWorld._21 * TargerPos.y + viewWorld._31 * TargerPos.z + viewWorld._41) * fViewW * Data::dwSightX;
	float fBoxY = Data::dwSightY - (viewWorld._12 * TargerPos.x + viewWorld._22 * TargerPos.y + viewWorld._32 * (TargerPos.z + 82) + viewWorld._42) * fViewW * Data::dwSightY;
	int nBoxY1 = Data::dwSightY - (viewWorld._12 * TargerPos.x + viewWorld._22 * TargerPos.y + viewWorld._32 * (TargerPos.z - 95) + viewWorld._42) * fViewW * Data::dwSightY;
	int nBoxH = nBoxY1 - fBoxY;

	result->x = fBoxX - nBoxH / 4;
	result->y = fBoxY;
	result->h = nBoxH;
	result->w = nBoxH / 2.5;
	return true;
}

bool GameData::WorldToScreen_2D(Matrix viewWorld, Vector3 TargerPos, Vector2* result)
{
	float fViewW = viewWorld._14 * TargerPos.x + viewWorld._24 * TargerPos.y + viewWorld._34 * TargerPos.z + viewWorld._44;
	if (fViewW < 0.01f) { return false; }
	fViewW = 1 / fViewW;
	float fBoxX = Data::dwSightX + (viewWorld._11 * TargerPos.x + viewWorld._21 * TargerPos.y + viewWorld._31 * TargerPos.z + viewWorld._41) * fViewW * Data::dwSightX;
	float fBoxY = Data::dwSightY - (viewWorld._12 * TargerPos.x + viewWorld._22 * TargerPos.y + viewWorld._32 * TargerPos.z + viewWorld._42) * fViewW * Data::dwSightY;
	result->x = fBoxX;
	result->y = fBoxY;
	return true;
}

void GameData::GetBonePosition(ULONG64 ObjectMesh, Vector3* resultPos, DWORD BoneId)
{
	FTransform bone, actor;
	Matrix boneMatrix, componentToWorldMatrix, newMatrix;
	ULONG64 dwBoneAddr;
	dwBoneAddr = ReadMem<ULONG64>(ObjectMesh + m_BoneArray); //骨骼指针
	bone = GameAlgorithm::ReadFTransform(dwBoneAddr + BoneId * 48);
	actor = GameAlgorithm::ReadFTransform(ObjectMesh + m_Spin);

	//printf("%.f\t%.f\t%.f\t%f\n", actor.Rotation.x, actor.Rotation.y, actor.Rotation.w, actor.Rotation.z);
	//printf("%.f\t%.f\t%.f\n", actor.Translation.x, actor.Translation.y, actor.Translation.z);
	//printf("%.f\t%.f\t%.f\n", actor.Scale3D.x, actor.Scale3D.y, actor.Scale3D.z);

	boneMatrix = GameAlgorithm::ToMatrixWithScale(bone.Rotation, bone.Translation, bone.Scale3D);
	componentToWorldMatrix = GameAlgorithm::ToMatrixWithScale(actor.Rotation, actor.Translation, actor.Scale3D);
	newMatrix = GameAlgorithm::D3DXMatrixMultiply(boneMatrix, componentToWorldMatrix);

	resultPos->x = newMatrix._41;
	resultPos->y = newMatrix._42;
	resultPos->z = newMatrix._43;
}

string GameData::GetPlayerName(ULONG64 Obj)
{
	WCHAR wstrName[64] = { '\0' };
	
	ReadVirtual(LPVOID(ReadMem<ULONG64>(Obj +m_Name)), &wstrName, sizeof(wstrName));
	USES_CONVERSION; // 声明这个宏要使用的局部变量
	char strObjName[64] = { '\0' };
	lstrcpy((LPWSTR)strObjName, (LPWSTR)OLE2A(wstrName));
	return strObjName;
}

string GameData::GetObjectName(ULONG64 Obj)
{
	WCHAR wstrName[64] = { '\0' };
	ReadVirtual(LPVOID(ReadMem<ULONG64>(ReadMem<ULONG64>(ReadMem<ULONG64>(Obj + m_ObjectRealNameOne) + m_ObjectRealNameTwo) ) ), &wstrName, sizeof(wstrName));
	USES_CONVERSION; // 声明这个宏要使用的局部变量
	char strObjName[64] = { '\0' };
	lstrcpy((LPWSTR)strObjName, (LPWSTR)OLE2A(wstrName));
	return strObjName;
}


bool GameData::isPlayer(string s)
{
	if(StrStrIA(s.c_str(),_xor_("BP_Prisoner_C"))!= NULL)
		return true;
	return false;
}

bool GameData::isBoom(string s)
{
	if (StrStrIA(s.c_str(),_xor_("Claymore")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("ImprovisedClaymore")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Mine_01")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Mine_02")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("PromTrap")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("StakePitTrap")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("PressureCookerBomb")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("CartridgeTrap")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("BarbedSpikeTrap")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Sensor_Detonator")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("ImprovisedMine")) != NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("PipeBomb")) != NULL)
		return true;
	return false;
}

bool GameData::isZombie(string s)
{
	if (StrStrIA(s.c_str(),_xor_("BP_Zombie_"))!= NULL)
		return true;
	return false;
}

bool GameData::isCar(string s)
{
	if (StrStrIA(s.c_str(),_xor_("Item"))== NULL)
	{
		if (StrStrIA(s.c_str(),_xor_("BP_SUV_01"))!= NULL)
			return true;
		else if (StrStrIA(s.c_str(),_xor_("BP_Pickup_01"))!= NULL)
			return true;
		else if (StrStrIA(s.c_str(),_xor_("BP_Quad_01"))!= NULL)
			return true;
	}
	return false;
}

bool GameData::isParts(string s)
{
	if (StrStrIA(s.c_str(),_xor_("BP_ScopeRail"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("BP_Magazine_"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("WeaponScope_"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("BP_WeaponSuppressor"))!= NULL)
		return true;
	return false;
}

bool GameData::isWeapon(string s)
{
	if (StrStrIA(s.c_str(),_xor_("BP_Weapon_"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("BPC_Weapon_"))!= NULL)
		return true;
	return false;
}

bool GameData::isPlane(string s)
{
	if (StrStrIA(s.c_str(),_xor_("Drone"))!= NULL)
		return true;
	return false;
}

bool GameData::isGoods(string s)
{
	if (StrStrIA(s.c_str(),_xor_("Screwdriver_C"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Lockpick_Item_C"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Bulletproof_Vest_05_C"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("Bulletproof_Vest_04_C"))!= NULL)
		return true;
	return false;
}

bool GameData::isAmmo(string s)
{
	if (StrStrIA(s.c_str(),_xor_("Cal"))!= NULL)
		return true;
	return false;
}

bool GameData::isBox(string s)
{
	if (StrStrIA(s.c_str(),_xor_("ImProvised_Metal_Chest_C"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("ImProvised_Wooden_Chest_C"))!= NULL)
		return true;
	else if (StrStrIA(s.c_str(),_xor_("BP_Mound_C"))!= NULL)
		return true;
	return false;
}

