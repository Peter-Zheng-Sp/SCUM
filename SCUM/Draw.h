#pragma once
#include <Windows.h>
#include <string>
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "imgui_impl_dx11.h"
#include"Struct.h"
class DrawUtil
{
public:
	static wchar_t* char2wchar(const char* cchar);//����ת��
};



namespace Draw
{
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ��ɫ;
	extern RGBA ������;
	extern RGBA ������;
	extern RGBA ������;
	extern RGBA ����;
	extern RGBA ����;
	extern RGBA ����;
	extern RGBA �ɺ�;
	extern RGBA ��ƺ��;
	extern RGBA ����;

	void DrawNewText(int x, int y, RGBA* color, const char* str);
	void DrawStrokeText(int x, int y, RGBA* color, const char* str);
	void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness);
	void DrawRectIm(int x, int y, int w, int h, ImVec4 color);
	void DrawFilledRect(int x, int y, int w, int h, RGBA* color);
	void DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments);
	void DrawCircle(int x, int y, int radius, RGBA* color, int segments);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne);
	void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color);
	void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness);
	void DrawLineIm(int x1, int y1, int x2, int y2, ImVec4 color);
	void DrawXBloodBar(MRect r,float Hp);
	void DrawYBloodBar(MRect r, float Hp);
}

