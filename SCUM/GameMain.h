#pragma once
#include"Struct.h"
#include"Data.h"
#include"Read.h"
#include"GameAlgorithm.h"
#include"GameData.h"
#include"Draw.h"
namespace GameMain
{
	void SetColor();
	void SetStyle();
	void RenderEsp();
	void RenderAim();
	void RenderSuper();
	void DataLoop();
	void DrawLoop();
	void DrawMenu();
	void FuncLoop();
	void DrawBone(ULONG64 ObjectMesh, Matrix m, RGBA* Color, int width);
}
