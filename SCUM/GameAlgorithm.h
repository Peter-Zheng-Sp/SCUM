#pragma once
#include"Struct.h"
#include"Data.h"
#include"GameData.h"
#include"Read.h"
namespace GameAlgorithm
{
	double Acos(double Value); //返回弧度值
	double Asin(double Value); //返回弧度值
	double RadianToAngle(double Value); //弧度转角度
	double AngleToRadian(double Value); //角度转弧度
	void AimBot(int x, int y, float AimSpeed); //自瞄
	Matrix D3DXMatrixMultiply(Matrix pM1, Matrix pM2);
	Matrix ToMatrixWithScale(Vector4 rotation, Vector3 Translation, Vector3 Scale3D);
	FTransform ReadFTransform(ULONG64 ptr);
	const char* GetNameFromFName(int key, ULONG64 fNamePool);
}
