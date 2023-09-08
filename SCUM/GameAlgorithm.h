#pragma once
#include"Struct.h"
#include"Data.h"
#include"GameData.h"
#include"Read.h"
namespace GameAlgorithm
{
	double Acos(double Value); //���ػ���ֵ
	double Asin(double Value); //���ػ���ֵ
	double RadianToAngle(double Value); //����ת�Ƕ�
	double AngleToRadian(double Value); //�Ƕ�ת����
	void AimBot(int x, int y, float AimSpeed); //����
	Matrix D3DXMatrixMultiply(Matrix pM1, Matrix pM2);
	Matrix ToMatrixWithScale(Vector4 rotation, Vector3 Translation, Vector3 Scale3D);
	FTransform ReadFTransform(ULONG64 ptr);
	const char* GetNameFromFName(int key, ULONG64 fNamePool);
}
