#include "GameAlgorithm.h"

double GameAlgorithm::Acos(double Value)
{
	if (Value > 1.f || Value < -1.f)
		return (0);
	return(3.1415 / 2.f - Asin(Value));
}

double GameAlgorithm::Asin(double Value)
{
	if (Value < -1.f || Value > 1.f)
		return 0;
	return (atan(Value / sqrt(1.f - Value * Value)));
}

double GameAlgorithm::RadianToAngle(double Value)
{
	return Value * 57.29577951308;
}

double GameAlgorithm::AngleToRadian(double Value)
{
	return Value * 0.01745329251944;
}

Matrix GameAlgorithm::D3DXMatrixMultiply(Matrix pM1, Matrix pM2)
{
	Matrix pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
	return pOut;
}

Matrix GameAlgorithm::ToMatrixWithScale(Vector4 Rotation, Vector3 Translation, Vector3 Scale3D)
{
	Matrix m;
	float x2, y2, z2, xx2, yy2, zz2, yz2, wx2, xy2, wz2, xz2, wy2;

	m._41 = Translation.x;
	m._42 = Translation.y;
	m._43 = Translation.z;

	x2 = Rotation.x + Rotation.x;
	y2 = Rotation.y + Rotation.y;
	z2 = Rotation.z + Rotation.z;

	xx2 = Rotation.x * x2;
	yy2 = Rotation.y * y2;
	zz2 = Rotation.z * z2;
	m._11 = (1 - (yy2 + zz2)) * Scale3D.x;
	m._22 = (1 - (xx2 + zz2)) * Scale3D.y;
	m._33 = (1 - (xx2 + yy2)) * Scale3D.z;

	yz2 = Rotation.y * z2;
	wx2 = Rotation.w * x2;
	m._32 = (yz2 - wx2) * Scale3D.z;
	m._23 = (yz2 + wx2) * Scale3D.y;

	xy2 = Rotation.x * y2;
	wz2 = Rotation.w * z2;
	m._21 = (xy2 - wz2) * Scale3D.y;
	m._12 = (xy2 + wz2) * Scale3D.x;


	xz2 = Rotation.x * z2;
	wy2 = Rotation.w * y2;
	m._31 = (xz2 + wy2) * Scale3D.z;
	m._13 = (xz2 - wy2) * Scale3D.x;

	m._14 = 0;
	m._24 = 0;
	m._34 = 0;
	m._44 = 1;

	return m;
}

FTransform GameAlgorithm::ReadFTransform(ULONG64 ptr)
{
	FTransform result;
	float date[12];
	ReadVirtual((LPVOID)ptr, date, 12 * sizeof(float));
	result.Rotation.x = date[0];
	result.Rotation.y = date[1];
	result.Rotation.z = date[2];
	result.Rotation.w = date[3];

	result.Translation.x = date[4];
	result.Translation.y = date[5];
	result.Translation.z = date[6];

	result.Scale3D.x = date[8];
	result.Scale3D.y = date[9];
	result.Scale3D.z = date[10];

	return result;
}

const char* GameAlgorithm::GetNameFromFName(int key,ULONG64 fNamePool)
{
	DWORD chunkOffset = ((int)(key) >> 16); // Block
	WORD nameOffset = key;
	auto namePoolChunk = ReadMem<ULONG64>(fNamePool + ((chunkOffset + 2) * 8));
	auto entryOffset = namePoolChunk + (DWORD)(2 * nameOffset);
	WORD nameLength = ReadMem<WORD>(entryOffset) >> 6;
	if (nameLength > 256)nameLength = 255;
	static char cBuf[256];
	ReadVirtual((LPVOID)(entryOffset + 2), cBuf, nameLength);
	cBuf[nameLength] = 0;
	return cBuf;
}

void GameAlgorithm::AimBot(int x, int y, float AimSpeed)
{
	int fTargetX = 0, fTargetY = 0;
	fTargetX = x - Data::dwSightX;
	fTargetY = y - Data::dwSightY;

	if (fTargetX > 0)
		fTargetX = GameData::toMove(fTargetX);
	else
		fTargetX = -GameData::toMove(fTargetX);


	if (fTargetY > 0)
		fTargetY = GameData::toMove(fTargetY);
	else
		fTargetY = -GameData::toMove(fTargetY);

	mouse_event(1, fTargetX/ AimSpeed, fTargetY/ AimSpeed, 0, 0);
}