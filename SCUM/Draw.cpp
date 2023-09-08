#include "Draw.h"

RGBA Draw::ºìÉ« = { 255,0,0,200 };
RGBA Draw::»ÆÉ« = { 255,255,0,180 };
RGBA Draw::À¶É« = { 0,0,255,200 };
RGBA Draw::ÂÌÉ« = { 0,255,0,255 };
RGBA Draw::»ÒÉ« = { 155,155,155,220 };
RGBA Draw::°×É« = { 255,255,255,220 };
RGBA Draw::ºÚÉ« = { 0, 0, 0,200 };
RGBA Draw::²£Á§ºÚ = { 0, 0, 0,160 };
RGBA Draw::²£Á§À¶ = { 65,105,225,80 };
RGBA Draw::²£Á§»Æ = { 255,255,0,160 };
RGBA Draw::ÇàÂÌ = { 144, 238 ,144,160 };
RGBA Draw::Àî×Ó = { 221,160,221,160 };
RGBA Draw::µ­À¶ = { 135,206,250,160 };
RGBA Draw::ĞÉºì = { 220, 20, 60,160 };
RGBA Draw::²İÆºÂÌ = { 124,252,0,180 };
RGBA Draw::²£Á§ = { 200,200,200,60 };


std::string string_To_UTF8(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = (int)(::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL));

    char* pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete[]pwBuf;
    delete[]pBuf;

    pwBuf = NULL;
    pBuf = NULL;

    return retStr;
}
wchar_t* DrawUtil::char2wchar(const char* cchar)
{
    wchar_t* m_wchar;
    int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
    m_wchar = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
    m_wchar[len] = '\0';
    return m_wchar;
}

void Draw::DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
{
    ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}

void Draw::DrawRectIm(int x, int y, int w, int h, ImVec4 color)
{
    ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0, 1);
}

void Draw::DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
    ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

void Draw::DrawCircleFilled(int x, int y, int radius, RGBA* color, int segments)
{
    ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

void Draw::DrawCircle(int x, int y, int radius, RGBA* color, int segments)
{
    ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments);
}

void Draw::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickne)
{
    ImGui::GetOverlayDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickne);
}

void Draw::DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color)
{
    ImGui::GetOverlayDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

void Draw::DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
    ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void Draw::DrawLineIm(int x1, int y1, int x2, int y2, ImVec4 color)
{
    ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(color), 1);
}

void Draw::DrawXBloodBar(MRect r, float Hp)
{
    RGBA* col;
    if (Hp > 100)
        Hp = 100;
    if (Hp > 75)
        col = &ÂÌÉ«;
    else if (Hp > 40)
        col = &»ÆÉ«;
    else
        col = &ºìÉ«;

    float dwDrawWidth = Hp * r.w / 100;
    DrawFilledRect(r.x - 6, r.y, 5, r.w, &ºÚÉ«);
    DrawFilledRect(r.x - 5, r.y +1, dwDrawWidth - 2,3, col);
}

void Draw::DrawYBloodBar(MRect r, float Hp)
{
    RGBA* col;
    if (Hp > 100)
        Hp = 100;
    if (Hp > 75)
        col = &ÂÌÉ«;
    else if (Hp > 40)
        col = &»ÆÉ«;
    else
        col = &ºìÉ«;

    float dwDrawWidth = Hp * r.h / 100;
    DrawFilledRect(r.x - 6, r.y, 5, r.h, &ºÚÉ«);
    DrawFilledRect(r.x - 5, r.y + r.h - dwDrawWidth + 1, 3, dwDrawWidth - 2, col);
}


void Draw::DrawNewText(int x, int y, RGBA* color, const char* str)
{
    ImFont a;
    std::string utf_8_1 = std::string(str);
    std::string utf_8_2 = string_To_UTF8(utf_8_1);
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}

void Draw::DrawStrokeText(int x, int y, RGBA* color, const char* str)
{
    ImFont a;
    std::string utf_8_1 = std::string(str);
    std::string utf_8_2 = string_To_UTF8(utf_8_1);

    ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), utf_8_2.c_str());
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), utf_8_2.c_str());
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), utf_8_2.c_str());
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), utf_8_2.c_str());
    ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}