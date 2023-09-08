#include "GameMain.h"
#include"GameBulletTrack.h"
#include"xorstr.hpp"

BYTE LockCode[2][8] = { { 243, 15, 92, 246, 144, 144, 144, 144 }, { 0xF3,0x0F,0x5C,0xB3,0xF8,0x03,0x00,0x00 } };
BYTE bullet[2][3]{ {0xB0,0x01,0x90 } ,{ 0x0F,0x9D,0xC0 } };
BYTE NoRecoil[3][8]{ { 144, 144, 144, 144, 144, 144, 144, 144 } ,{0xF3,0x0F,0x11,0x83,0xA4,0x13,0x00,0x00}, {0xF3,0x0F,0x11,0x83,0xA8,0x13,0x00,0x00} };
bool bPlayer, bZombie;
ULONG64 carPtr = 0;
int iTab;

void GameMain::SetColor()
{
	ImColor mainColor = ImColor(int(54), int(54), int(54), 255);
	ImColor bodyColor = ImColor(int(24), int(24), int(24), 255);
	ImColor fontColor = ImColor(int(255), int(255), int(255), 255);

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
	ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
	ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
	ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
	ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

	style.Colors[ImGuiCol_Text] = ImColor(254, 254, 254, 255);

	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(26, 26, 26, 255);
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(18, 18, 18, 255);
	style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
	style.Colors[ImGuiCol_Border] = ImColor(18, 18, 18, 0);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_TitleBg] = mainColor;
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = mainColor;
	style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
	style.Colors[ImGuiCol_ScrollbarGrab] = mainColor;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_ComboBg] = ImColor(14, 14, 14, 255);
	style.Colors[ImGuiCol_CheckMark] = ImColor(173, 102, 45, 255);
	style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
	style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
	style.Colors[ImGuiCol_Button] = ImColor(18, 18, 18, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(169, 79, 12);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(199, 79, 13);
	style.Colors[ImGuiCol_Header] = mainColor;
	style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
	style.Colors[ImGuiCol_HeaderActive] = mainColorActive;

	style.Colors[ImGuiCol_Column] = mainColor;
	style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ColumnActive] = mainColorActive;

	style.Colors[ImGuiCol_ResizeGrip] = mainColor;
	style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
	style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
	style.Colors[ImGuiCol_CloseButton] = mainColor;
	style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
	style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
	style.Colors[ImGuiCol_PlotLines] = mainColor;
	style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
	style.Colors[ImGuiCol_PlotHistogram] = mainColor;
	style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void GameMain::SetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(16, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(4, 3);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 8.f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 1.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;
	style.FrameBorderSize = 1.0f;
}

void GameMain::RenderEsp()
{
	ImGui::Text("\n");
	ImGui::TextColored(ImColor(199, 79, 13), u8"͸��ѡ��");
	ImGui::Separator();
	ImGui::Text("\n");
	ImGui::Checkbox(u8"��ҷ���", &Data::op.playerBox);
	ImGui::SameLine();
	ImGui::Checkbox(u8"�����Ϣ", &Data::op.playerInfo);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��ҹ���", &Data::op.playerbone);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��ʬ����", &Data::op.zombieBox);

	ImGui::Text("\n");
	ImGui::Checkbox(u8"��ʬ��Ϣ", &Data::op.zombieInfo);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��ʬ����", &Data::op.zombiebone);
	ImGui::SameLine();
	ImGui::Checkbox(u8"���˻�   ", &Data::op.plane);
	ImGui::SameLine();
	ImGui::Checkbox(u8"����       ", &Data::op.car);

	ImGui::Text("\n");
	ImGui::Checkbox(u8"��Ʒ       ", &Data::op.goods);
	ImGui::SameLine();
	ImGui::Checkbox(u8"���       ", &Data::op.parts);
	ImGui::SameLine();
	ImGui::Checkbox(u8"�ӵ�       ", &Data::op.ammo);
	ImGui::SameLine();
	ImGui::Checkbox(u8"ľ��       ", &Data::op.box);

	ImGui::Text("\n");
	ImGui::Checkbox(u8"����       ", &Data::op.boom);
	ImGui::SameLine();
	ImGui::Checkbox(u8"����        ", &Data::op.weapon);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��ʾ׼��", &Data::op.crosshare);
	ImGui::Text("\n");
}

void GameMain::RenderAim()
{

	const char* parts[] = { u8"ͷ��",u8"�ؿ�",u8"����" };
	const char* type[] = { u8"��",u8"׷��",u8"ħ��",u8"����" };
	ImGui::Text("\n");
	ImGui::TextColored(ImColor(199, 79, 13), u8"����ѡ��");
	ImGui::Separator();
	ImGui::Text("\n");
	ImGui::Checkbox(u8"���鷶Χ", &Data::op.showScope);
	ImGui::Combo(u8"�����λ",&Data::op.aimPart, parts,3);
	ImGui::Combo(u8"��������", &Data::op.aimType, type, 4);
	

	ImGui::Text("\n");
	ImGui::TextColored(ImColor(199, 79, 13), u8"��������");
	ImGui::Separator();
	ImGui::Text("\n");
	ImGui::SliderFloat(u8"��Χ����", &Data::op.aimScope,50,300,"%.f");
	ImGui::SliderFloat(u8"�����ٶ�", &Data::op.aimSpeed, 1, 10,"%.f");
}

void GameMain::RenderSuper()
{
	ImGui::Text("\n");
	ImGui::TextColored(ImColor(199, 79, 13), u8"�߼�ѡ��");
	ImGui::Separator();
	ImGui::Text("\n");
	ImGui::Checkbox(u8"�������", &Data::op.superSpeed);
	ImGui::SameLine();
	ImGui::Checkbox(u8"����       ", &Data::op.gatherPlayer);
	ImGui::SameLine();
	ImGui::Checkbox(u8"����ʬ   ", &Data::op.gatherZombie);
	ImGui::SameLine();
	ImGui::Checkbox(u8"���ﴩǽ", &Data::op.noCollision);

	ImGui::Text("\n");
	ImGui::Checkbox(u8"�������", &Data::op.hightJump);
	ImGui::SameLine();
	ImGui::Checkbox(u8"�����޺�", &Data::op.noRecoil);
	ImGui::SameLine();
	ImGui::Checkbox(u8"�����ӵ�", &Data::op.unlimitBullet);
	ImGui::SameLine();
	ImGui::Checkbox(u8"������", &Data::op.gost);

	ImGui::Text("\n");
	ImGui::Checkbox(u8"���޽���", &Data::op.unlimitMake);
	ImGui::SameLine();
	ImGui::Checkbox(u8"���Ӻ�ҹ", &Data::op.noNight);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��������", &Data::op.unLock);
	ImGui::SameLine();
	ImGui::Checkbox(u8"���ӵ���", &Data::op.noMakeCondic);

	ImGui::Text("\n");
	
	ImGui::Checkbox(u8"��������", &Data::op.carSpeed);
	ImGui::SameLine();
	ImGui::Checkbox(u8"��������", &Data::op.carSky);

	ImGui::Text("\n");
	ImGui::TextColored(ImColor(199, 79, 13), u8"�߼�����");
	ImGui::Separator();
	ImGui::Text("\n");
	ImGui::SliderFloat(u8"���ٱ���", &Data::op.speedSize, 1, 30, "%.f");
	ImGui::SliderFloat(u8"��������", &Data::op.jumpSize, 0.1, 1, "%.1f");
	ImGui::SliderFloat(u8"�����ٶ�", &Data::op.carSpeedSize, 100, 1000, "%.1f");
}

void GameMain::DrawMenu()
{

	if (Data::op.isShow)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::Begin(u8"op-Scum   [Home��ʾ / ���ز˵�  End ��ȫ�˳�]", &Data::op.isShow, ImVec2(475, 240), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
		{
			ImGui::SetWindowSize(ImVec2(475, 240));
			ImGui::Text(u8"op-Scum   [Home��ʾ / ���ز˵�  End ��ȫ�˳�]");
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 120);
			style.ItemSpacing = ImVec2(0.f, 0.f);
			ImGui::BeginChild("##tabs", ImVec2(100, 200), false);
			{
				style.Colors[ImGuiCol_Button] = iTab == 0 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
				if (ImGui::Button(u8"͸��", ImVec2(100, 45))) iTab = 0;
				style.Colors[ImGuiCol_Button] = iTab == 1 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
				if (ImGui::Button(u8"����", ImVec2(100, 45))) iTab = 1;
				style.Colors[ImGuiCol_Button] = iTab == 2 ? ImColor(199, 79, 13) : ImColor(18, 18, 18, 255);
				if (ImGui::Button(u8"�߼�", ImVec2(100, 45))) iTab = 2;
			}ImGui::EndChild();
			ImGui::NextColumn();
			SetStyle();
			SetColor();
			ImGui::BeginChild("##main", ImVec2(337, 200), true);
			{
				switch (iTab)
				{
				case 0:
					RenderEsp();
					break;
				case 1:
					RenderAim();
					break;
				case 2:
					RenderSuper();
					break;
				}
			}ImGui::EndChild();
		}
		ImGui::End();
	}

}

void GameMain::FuncLoop()
{
	if (Data::op.showScope)
		Draw::DrawCircle(Data::dwSightX,Data::dwSightY,Data::op.aimScope,&Draw::��ɫ,100);
	if (Data::g_LocalPlayer.Object > 0)
	{
		static char text[256];
		//����
		if (Data::op.hightJump)
			WriteMem<FLOAT>(ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_CharacterMove) + m_HightJump, Data::op.jumpSize);
		else
			WriteMem<FLOAT>(ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_CharacterMove) + m_HightJump, 1.f);

		//�������
		if (Data::op.superSpeed)
			WriteMem<FLOAT>(Data::g_LocalPlayer.Object + m_InpawnSpeedSize, Data::op.speedSize);
		else
			WriteMem<FLOAT>(Data::g_LocalPlayer.Object + m_InpawnSpeedSize, 1.f);

		//������
		if (Data::op.gost)
			WriteMem<BYTE>(Data::g_LocalPlayer.Object + m_Gost, 0);
		else
			WriteMem<BYTE>(Data::g_LocalPlayer.Object + m_Gost, 144);

		//�޲��Ͻ���
		if (Data::op.unlimitMake)
			WriteMem<DWORD>(Data::g_LocalPlayer.Object + m_UnlimitMake, 1);
		else
			WriteMem<BYTE>(Data::g_LocalPlayer.Object + m_UnlimitMake, 0);

		//��������
		if (Data::op.unLock)
			WriteVirtual(LPVOID(Data::BaseModule + m_UnLock), LockCode[0],8);
		else
			WriteVirtual(LPVOID(Data::BaseModule + m_UnLock), LockCode[1],8);

		//���ﴩǽ
		if (Data::op.noCollision)
		{
			if (GetAsyncKeyState(87) != 0 && GetAsyncKeyState(16) != 0)
				WriteMem<BYTE>(Data::BaseModule + m_ThroughWallHook, 116);
			else
				WriteMem<BYTE>(Data::BaseModule + m_ThroughWallHook, 117);
		}

		//���Ӻ�ҹ
		if (Data::op.noNight)
		{
			FLOAT timeAddr = ReadMem<FLOAT>(ReadMem<ULONG64>(ReadMem<ULONG64>(ReadMem<ULONG64>(Data::BaseModule + m_GameTime) + m_offsetOne) + m_offsetTwo) + m_offsetThree);
			FLOAT v = -1;
			//printf("Data::g_Ue4Engine.ScreenAddr:%llx,timeAddr:%llx\n", Data::g_Ue4Engine.ScreenAddr,ReadMem<ULONG64>(ReadMem<ULONG64>(ReadMem<ULONG64>(Data::BaseModule + m_GameTime) + m_offsetOne) + m_offsetTwo) + m_offsetThree);
			if ((timeAddr >= 1 and timeAddr <= 4) || timeAddr == 21)
				v = 10;
			else if (timeAddr == 5)
				v = 4;
			else if (timeAddr == 6 || timeAddr == 20)
				v = 2;
			else if (timeAddr == 22 || timeAddr == 23)
				v = 25;
			else if (timeAddr == 0)
				v = 15;

			if (v != -1)
			{
				WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr, v);
				WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr + 4, v);
				WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr + 8, v);
			}
		}
		else
		{
			WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr, 1);
			WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr + 4, 1);
			WriteMem<FLOAT>(Data::g_Ue4Engine.ScreenAddr + 8, 1);
		}

		//����
		if (Data::op.gatherPlayer)
		{
			sprintf(text, "F1 ǧ�������ࣺ %s", bPlayer ? "����" : "�ر�");
			Draw::DrawStrokeText(Data::dwSightX - 10, 80, &Draw::��ɫ, text);
			if (GetAsyncKeyState(112) != 0)
			{
				bPlayer = !bPlayer;
				Sleep(200);
			}
		}

		//����ʬ
		if (Data::op.gatherZombie)
		{
			sprintf(text, "F2 ǧ������ʬ�� %s", bZombie ? "����" : "�ر�");
			Draw::DrawStrokeText(Data::dwSightX - 10, 100, &Draw::��ɫ, text);
			if (GetAsyncKeyState(113) != 0)
			{
				bZombie = !bZombie;
				Sleep(200);
			}
		}

		//��������
		if (Data::op.carSpeed)
		{
			ULONG64 addr = ReadMem<ULONG64>(ReadMem<ULONG64>(carPtr + 0x288) + 0x228) + 0x730;
			Draw::DrawStrokeText(Data::dwSightX, Data::dwSightY, &Draw::��ɫ, "�� �� �� �� �� �� ����");
			if (GetAsyncKeyState(16) != 0)
			{
				WriteMem<FLOAT>(addr, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 4, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 8, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 12, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 16, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 20, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 24, Data::op.carSpeedSize);
				WriteMem<FLOAT>(addr + 28, Data::op.carSpeedSize);
			}
		}

		//��������
		if (Data::op.carSky)
		{
			ULONG64 addr = ReadMem<ULONG64>(ReadMem<ULONG64>(ReadMem<ULONG64>(carPtr + 0x288) + 0x228) + 0xA0) + 0x15C;

			FLOAT Clockwise = ReadMem<FLOAT>(Data::g_Ue4Engine.MouseAddr+4);
			Draw::DrawStrokeText(Data::dwSightX, Data::dwSightY-20, &Draw::��ɫ, "���������Ѵ򿪣��ո�� ����  С�����������ҿ��Ʒ��� ��С�ļ�ʻ��");
			if (GetAsyncKeyState(38) != 0)//UP
			{
				WriteMem<FLOAT>(addr, ReadMem<FLOAT>(addr) + cos(GameAlgorithm::AngleToRadian(Clockwise)) * 60);
				WriteMem<FLOAT>(addr + 4, ReadMem<FLOAT>(addr + 4) + sin(GameAlgorithm::AngleToRadian(Clockwise)) * 60);

			}
			if (GetAsyncKeyState(40) != 0)//DOWN
			{

				WriteMem<FLOAT>(addr, ReadMem<FLOAT>(addr) + cos(GameAlgorithm::AngleToRadian(Clockwise + 180)) * 60);
				WriteMem<FLOAT>(addr + 4, ReadMem<FLOAT>(addr + 4) + sin(GameAlgorithm::AngleToRadian(Clockwise + 180)) * 60);

			}
			if (GetAsyncKeyState(37) != 0)//LEFT
			{
				WriteMem<FLOAT>(addr, ReadMem<FLOAT>(addr) + cos(GameAlgorithm::AngleToRadian(Clockwise - 90)) * 60);
				WriteMem<FLOAT>(addr + 4, ReadMem<FLOAT>(addr + 4) + sin(GameAlgorithm::AngleToRadian(Clockwise - 90)) * 60);

			}
			if (GetAsyncKeyState(39) != 0)//RIGHT
			{
				WriteMem<FLOAT>(addr, ReadMem<FLOAT>(addr) + cos(GameAlgorithm::AngleToRadian(Clockwise + 90)) * 60);
				WriteMem<FLOAT>(addr + 4, ReadMem<FLOAT>(addr + 4) + sin(GameAlgorithm::AngleToRadian(Clockwise + 90)) * 60);
			}
			if (GetAsyncKeyState(32) != 0)//Space
			{
				WriteMem<FLOAT>(addr + 8, ReadMem<FLOAT>(addr + 8) + 50);
			}
		}

		int aimPart = 64, aimIndex = 0;;
		FLOAT TempDis[2]{ -1,-1 };
		if (Data::g_LocalPlayer.WeaponPtr > 0)
		{
			if (Data::op.aimPart == 0)
				aimPart = 64;
			else if (Data::op.aimPart == 1)
				aimPart = 42;
			else if (Data::op.aimPart == 2)
				aimPart = 1;

			if (Data::aimBot[0].dwObj != 0) //�ж��Ƿ��п���׼������
				TempDis[0] = Data::aimBot[0].Value2;
			if (Data::aimBot[1].dwObj != 0) //�ж��Ƿ��п���׼�Ľ�ʬ
				TempDis[1] = Data::aimBot[1].Value2;

			if (TempDis[0] != -1 || TempDis[1] == -1)// ������û�н�ʬ
				aimIndex = 0;
			if (TempDis[0] == -1 || TempDis[1] != -1)//�н�ʬû������
				aimIndex = 1;
			if (TempDis[0] != -1 && TempDis[1] != -1)//�н�ʬҲ������
			{
				if (TempDis[0] < TempDis[1] )//�������ľ���Ƚ�ʬ����С
					aimIndex = 0;
				else
					aimIndex = 1;
			}
			if (TempDis[0] == -1 && TempDis[1] == -1)
				aimIndex = 0;

			//�����ӵ�
			if (Data::op.unlimitBullet)
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponBullet), bullet[0],3);
			else
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponBullet), bullet[1],3);

			//�޺���
			if (Data::op.noRecoil)
			{
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponShakeYHook), NoRecoil[0], 8);
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponShakeXHook), NoRecoil[0], 8);
			}
			else
			{
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponShakeYHook), NoRecoil[1], 8);
				WriteVirtual(LPVOID(Data::BaseModule + m_WeaponShakeXHook), NoRecoil[2], 8);
			}
			if (Data::aimBot[aimIndex].dwObj > 0)
			{
				if (Data::op.aimType == 1)//����׷��
				{
					if (GetAsyncKeyState(1) != 0)
					{
						Data::aimBot[aimIndex].bLook = true;
						Vector3 inpawn,enemy;
						inpawn = GameData::ReadVector3(Data::g_Ue4Engine.CameraPos,0);
						GameData::GetBonePosition(Data::aimBot[aimIndex].dwObjMesh, &enemy, aimPart);
						GameBulletTrack::BulletTrack(true, inpawn, enemy);
					}
					else
					{
						Data::aimBot[aimIndex].bLook = false;
						Data::aimBot[aimIndex].dwObj = 0;
						Data::aimBot[aimIndex].dwObjMesh = 0;
						Data::aimBot[aimIndex].Value1 = 0;
						Data::aimBot[aimIndex].Value2 = 0;
						GameBulletTrack::BulletTrack(false, {}, {});
					}
				}
				else if (Data::op.aimType == 2) //ħ���ӵ�
				{
					if (GetAsyncKeyState(1) != 0)
					{
						Data::aimBot[aimIndex].bLook = true;
						Vector3 enemy;
						GameData::GetBonePosition(Data::aimBot[aimIndex].dwObjMesh, &enemy, aimPart);
						GameBulletTrack::MagicBullet(true,  enemy);
					}
					else
					{
						Data::aimBot[aimIndex].bLook = false;
						Data::aimBot[aimIndex].dwObj = 0;
						Data::aimBot[aimIndex].dwObjMesh = 0;
						Data::aimBot[aimIndex].Value1 = 0;
						Data::aimBot[aimIndex].Value2 = 0;
						GameBulletTrack::MagicBullet(false, {});
					}
				}
				else if (Data::op.aimType == 3) //����
				{
					if (GetAsyncKeyState(2) != 0)
					{
						Data::aimBot[aimIndex].bLook = true;
						Vector2 out;
						Vector3 pos;
						GameData::GetBonePosition(Data::aimBot[aimIndex].dwObjMesh, &pos, aimPart);
						if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, pos, &out))
						{
							GameAlgorithm::AimBot(out.x, out.y, Data::op.aimSpeed);
						}
					}
					else
					{
						Data::aimBot[aimIndex].bLook = false;
						Data::aimBot[aimIndex].dwObj = 0;
						Data::aimBot[aimIndex].dwObjMesh = 0;
						Data::aimBot[aimIndex].Value1 = 0;
						Data::aimBot[aimIndex].Value2 = 0;
					}
				}
			}
		}
	}
}

void GameMain::DataLoop()
{
	ObjArray tmpObjArray;
	while (true)
	{
		//�������
		tmpObjArray.player.clear();
		tmpObjArray.zombie.clear();
		tmpObjArray.boom.clear();
		tmpObjArray.box.clear();
		tmpObjArray.parts.clear();
		tmpObjArray.other.clear();
		tmpObjArray.weapon.clear();
		tmpObjArray.goods.clear();
		tmpObjArray.ammo.clear();
		tmpObjArray.plane.clear();
		tmpObjArray.car.clear();

		//��ȡ����
		Data::dwSightX = ReadMem<DWORD>(Data::BaseModule + m_Screen) / 2;
		Data::dwSightY = ReadMem<DWORD>(Data::BaseModule + m_Screen + 4) / 2;
		Data::g_Ue4Engine.pUworld = ReadMem<ULONG64>(Data::BaseModule + m_Uworld);
		Data::g_Ue4Engine.pGname = Data::BaseModule + m_Gname;
		Data::g_Ue4Engine.pMatrix = Data::BaseModule + m_Matrix;
		if (NULL != Data::g_Ue4Engine.pUworld)
		{
			GameData::GetMatrix(Data::g_Ue4Engine.pMatrix, &Data::g_Ue4Engine.ViewWorld);
			Data::g_Ue4Engine.pUlevel = ReadMem<ULONG64>(Data::g_Ue4Engine.pUworld + m_ULevel);
			Data::g_Ue4Engine.ActorArray = ReadMem<ULONG64>(Data::g_Ue4Engine.pUlevel + m_Actor);
			Data::g_Ue4Engine.ActorCount = ReadMem<DWORD>(Data::g_Ue4Engine.pUlevel + m_Actor + 8);
			if (0 < Data::g_Ue4Engine.ActorCount)
			{
				Data::g_Ue4Engine.GameInstance = ReadMem<ULONG64>(Data::g_Ue4Engine.pUworld + m_GameInstance);
				Data::g_Ue4Engine.LocalPlayer = ReadMem<ULONG64>(ReadMem<ULONG64>(Data::g_Ue4Engine.GameInstance + m_LocalPlayer));
				Data::g_Ue4Engine.PlayerController = ReadMem<ULONG64>(Data::g_Ue4Engine.LocalPlayer + m_PlayerController);
				Data::g_Ue4Engine.CameraPos = Data::g_Ue4Engine.LocalPlayer + m_CameraPos;
				Data::g_Ue4Engine.MouseAddr = Data::g_Ue4Engine.PlayerController + m_Mouse;
				Data::g_Ue4Engine.ScreenAddr = ReadMem<ULONG64>(Data::g_Ue4Engine.PlayerController + m_CameraManager)+m_CanSee;

				Data::g_LocalPlayer.Object = ReadMem<ULONG64>(Data::g_Ue4Engine.PlayerController + m_Inpawn);
				Data::g_LocalPlayer.Mesh = ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_Mesh);

				//��ȡ������ַ
				ULONG64 InventoryPtr= ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_Inventory);
				DWORD InventoryCount = ReadMem<DWORD>(Data::g_LocalPlayer.Object + m_Inventory+8);
				for (int i = 0; i < InventoryCount; i++)
				{
					carPtr = ReadMem<ULONG64>(InventoryPtr + 8 * i);
					string typeName = GameAlgorithm::GetNameFromFName(ReadMem<DWORD>(carPtr + m_ObjectId), Data::g_Ue4Engine.pGname);
					//printf("%s\n", typeName.c_str());
					if (GameData::isCar(typeName))
					{
						//printf("%llx\n",carPtr);
						break;
					}
					carPtr = 0;
				}
					
				if (0 < Data::g_LocalPlayer.Object)
				{
					//�ж��Ƿ��ڽ���
					if (GameData::GetPlayerName(Data::g_LocalPlayer.Object).empty())
					{
						Data::isGameMenu = true;
						continue;
					}
					else
					{
						Data::isGameMenu = false;
					}
					Data::g_LocalPlayer.WeaponPtr= ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_WeaponPtr);
					Data::g_LocalPlayer.Mesh = ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_Mesh);
					Data::g_LocalPlayer.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(Data::g_LocalPlayer.Object + m_RootComponent),m_Vector3);
					Object<ULONG64> obj;
					for (int i = 0; i <= Data::g_Ue4Engine.ActorCount; i++)
					{
						obj.Object= ReadMem<ULONG64>(Data::g_Ue4Engine.ActorArray + i * 8);
						if (obj.Object <= 0)
							continue;
						else if (obj.Object == Data::g_LocalPlayer.Object)
							continue;

						obj.ObjectId = ReadMem<DWORD>(obj.Object+m_ObjectId);
						obj.ObjectType=GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
						
						if (GameData::isPlayer(obj.ObjectType)  && (Data::op.playerBox || Data::op.playerInfo  || Data::op.playerbone))
						{
							tmpObjArray.player.push_back(obj.Object);
							continue;
						}
						else if (GameData::isZombie(obj.ObjectType) && (Data::op.zombieBox || Data::op.zombieInfo || Data::op.zombiebone))
						{
							tmpObjArray.zombie.push_back(obj.Object);
							continue;
						}
						else if (GameData::isCar(obj.ObjectType) && (Data::op.car))
						{
							tmpObjArray.car.push_back(obj.Object);
							continue;
						}
						else if (GameData::isParts(obj.ObjectType) && (Data::op.parts))
						{
							tmpObjArray.parts.push_back(obj.Object);
							continue;
						}
						else if (GameData::isGoods(obj.ObjectType) && (Data::op.goods))
						{
							tmpObjArray.goods.push_back(obj.Object);
							continue;
						}
						else if (GameData::isWeapon(obj.ObjectType) && (Data::op.weapon))
						{
							tmpObjArray.weapon.push_back(obj.Object);
							continue;
						}
						else if (GameData::isAmmo(obj.ObjectType) && (Data::op.ammo))
						{
							tmpObjArray.ammo.push_back(obj.Object);
							continue;
						}
						else if (GameData::isBox(obj.ObjectType) && (Data::op.box))
						{
							tmpObjArray.box.push_back(obj.Object);
							continue;
						}
						else if (GameData::isPlane(obj.ObjectType) && (Data::op.plane))
						{
							tmpObjArray.plane.push_back(obj.Object);
							continue;
						}
						else if (GameData::isBoom(obj.ObjectType) && (Data::op.boom))
						{
							tmpObjArray.boom.push_back(obj.Object);
							continue;
						}

						if (StrStrA(obj.ObjectType.c_str(),_xor_("WeaponBullet"))!=NULL)
						{
							Data::MagicBulletValue = ReadMem<DWORD>(ReadMem<ULONG64>(obj.Object+m_RootComponent)+m_ObjectId);
							WriteMem<DWORD>(Data::BaseModule+m_Space+256+80, Data::MagicBulletValue);
							continue;
						}
						//Debug����
						tmpObjArray.other.push_back(obj.Object);
					}
				}
			}
		}
		Data::g_ObjArray=tmpObjArray;

		//����
		if (bPlayer)
		{
			for (auto i : tmpObjArray.player)
			{
				WriteMem<FLOAT>(ReadMem<ULONG64>(i+m_RootComponent)+m_Vector3,Data::g_LocalPlayer.Vector3d.x-500);
				WriteMem<FLOAT>(ReadMem<ULONG64>(i + m_RootComponent) + m_Vector3+4, Data::g_LocalPlayer.Vector3d.y - 500);
				WriteMem<FLOAT>(ReadMem<ULONG64>(i + m_RootComponent) + m_Vector3+8, Data::g_LocalPlayer.Vector3d.z);
			}
		}

		//����ʬ
		if (bZombie)
		{
			for (auto i : tmpObjArray.zombie)
			{
				WriteMem<FLOAT>(ReadMem<ULONG64>(i + m_RootComponent) + m_Vector3, Data::g_LocalPlayer.Vector3d.x - 500);
				WriteMem<FLOAT>(ReadMem<ULONG64>(i + m_RootComponent) + m_Vector3 + 4, Data::g_LocalPlayer.Vector3d.y - 500);
				WriteMem<FLOAT>(ReadMem<ULONG64>(i + m_RootComponent) + m_Vector3 + 8, Data::g_LocalPlayer.Vector3d.z);
			}
		}
	}
}

void GameMain::DrawLoop()
{
	char dis[256];
	int nameLength = 0;
	MRect rect,blood;
	Vector2 out;
	Object<ULONG64> obj;
	ObjArray tmpObjArray;
	tmpObjArray = Data::g_ObjArray;
	GameData::GetMatrix(Data::g_Ue4Engine.pMatrix, &Data::g_Ue4Engine.ViewWorld);

	if (Data::op.crosshare)
	{
		//��׼��
		Draw::DrawLine(Data::dwSightX - 15, Data::dwSightY, Data::dwSightX + 15, Data::dwSightY, &Draw::��ɫ, 1);
		Draw::DrawLine(Data::dwSightX, Data::dwSightY - 15, Data::dwSightX, Data::dwSightY + 15, &Draw::��ɫ, 1);
	}


	if (tmpObjArray.plane.size() > 0)
	{
		sprintf(dis,"Tip�����������˻�[%d]", tmpObjArray.plane.size());
		Draw::DrawStrokeText(Data::dwSightX-50,120,&Draw::��ɫ, dis);
	}

	//���
	for (auto addr : tmpObjArray.player)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.Mesh = ReadMem<ULONG64>(obj.Object + m_Mesh);
		obj.ObjectName = GameData::GetPlayerName(obj.Object);
		if (GameData::WorldToScreen_3D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &rect))
		{
			if (!Data::aimBot[0].bLook)
			{
				Data::aimBot[0].Value1 = GameData::Get2dDistance(Data::dwSightX, Data::dwSightY, rect.x + rect.w / 2, rect.y);
				if (Data::aimBot[0].Value1 <= Data::op.aimScope)
				{
					if (Data::aimBot[0].Value2 == 0)
					{
						Data::aimBot[0].Value2 = Data::aimBot[0].Value1;
						Data::aimBot[0].dwObj = obj.Object;
						Data::aimBot[0].dwObjMesh = obj.Mesh;
					}
					else if (Data::aimBot[0].Value1 < Data::aimBot[0].Value2)
					{
						Data::aimBot[0].Value2 = Data::aimBot[0].Value1;
						Data::aimBot[0].dwObj = obj.Object;
						Data::aimBot[0].dwObjMesh = obj.Mesh;
					}
				}
			}

			if (Data::op.playerbone)
				DrawBone(obj.Mesh, Data::g_Ue4Engine.ViewWorld, &Draw::��ɫ, 2);
			if(Data::op.playerBox)
				Draw::DrawRect(rect.x, rect.y, rect.w, rect.h, Data::aimBot[0].dwObj == obj.Object? &Draw::��ɫ: &Draw::��ɫ, 1);
			if (Data::op.playerInfo)
			{
				nameLength = strlen(obj.ObjectName.c_str());
				Draw::DrawStrokeText(rect.x + rect.w / 2 - nameLength * 3, rect.y - 16, &Draw::��ɫ, obj.ObjectName.c_str());

				sprintf(dis, "%.f", obj.Distance);
				Draw::DrawStrokeText(rect.x + rect.w / 2 - strlen(dis) * 3, rect.y + rect.h + 1, &Draw::��ɫ, dis);
				GameData::GetBonePosition(obj.Mesh, &obj.Vector3d, 66);
				if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
				{
					Draw::DrawCircleFilled(out.x, out.y, 2, &Draw::��ɫ, 100);
				}
			}
		}
	}
	//��ʬ
	for (auto addr : tmpObjArray.zombie)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object+m_RootComponent),m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d,100); 
		obj.Mesh = ReadMem<ULONG64>(obj.Object + m_Mesh);
		obj.ObjectHp= ReadMem<FLOAT>(obj.Object + m_ZombieHp)*100;
		if (obj.ObjectHp <= 0)
			continue;
		if (GameData::WorldToScreen_3D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &rect))
		{
			if (!Data::aimBot[1].bLook)
			{
				Data::aimBot[1].Value1 = GameData::Get2dDistance(Data::dwSightX, Data::dwSightY, rect.x + rect.w / 2, rect.y);
				if (Data::aimBot[1].Value1 <= Data::op.aimScope)
				{
					if (Data::aimBot[1].Value2 == 0)
					{
						Data::aimBot[1].Value2 = Data::aimBot[1].Value1;
						Data::aimBot[1].dwObj = obj.Object;
						Data::aimBot[1].dwObjMesh = obj.Mesh;
					}
					else if (Data::aimBot[1].Value1 < Data::aimBot[1].Value2)
					{
						Data::aimBot[1].Value2 = Data::aimBot[1].Value1;
						Data::aimBot[1].dwObj = obj.Object;
						Data::aimBot[1].dwObjMesh = obj.Mesh;
					}
				}
			}

			if (Data::op.zombiebone)
				DrawBone(obj.Mesh,Data::g_Ue4Engine.ViewWorld,&Draw::��ɫ,2);
			if(Data::op.zombieBox)
				Draw::DrawRect(rect.x,rect.y,rect.w,rect.h, Data::aimBot[1].dwObj == obj.Object ? &Draw::��ɫ : &Draw::��ɫ,1);
			if (Data::op.zombieInfo)
			{
				blood.x = rect.x - 1;
				blood.y = rect.y;
				blood.w = 1;
				blood.h = rect.h;
				Draw::DrawYBloodBar(blood, obj.ObjectHp * 2.85);
				nameLength = strlen("Zombie");
				Draw::DrawStrokeText(rect.x + rect.w / 2 - nameLength * 3, rect.y - 16, &Draw::��ɫ, "Zombile");

				sprintf(dis, "%.f", obj.Distance);
				Draw::DrawStrokeText(rect.x + rect.w / 2 - strlen(dis) * 3, rect.y + rect.h + 1, &Draw::��ɫ, dis);
				GameData::GetBonePosition(obj.Mesh, &obj.Vector3d, 66);
				if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
				{
					Draw::DrawCircleFilled(out.x, out.y, 2, &Draw::��ɫ, 100);
				}
			}
		}
	}
	//��
	for (auto addr : tmpObjArray.car)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		if (StrStrIA(obj.ObjectType.c_str(), _xor_("SUV")) != NULL)
			obj.ObjectRealName="�����";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("Pickup")) != NULL)
			obj.ObjectRealName = "Ƥ��";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("Quad")) != NULL)
			obj.ObjectRealName = "Ħ�г�";
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 255,0,255,255 }, dis);
		}
	}
	//���
	for (auto addr : tmpObjArray.parts)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 255,0,255,255 }, dis);
		}
	}
	//��Ʒ
	for (auto addr : tmpObjArray.goods)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 255,255,255,255 }, dis);
		}
	}
	//����   
	for (auto addr : tmpObjArray.weapon)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 255,128,0,255 }, dis);
		}
	}
	//�ӵ�   
	for (auto addr : tmpObjArray.ammo)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 0,136,255,255 }, dis);
		}
	}
	//ľ��
	for (auto addr : tmpObjArray.box)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]", obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 168,176,255,255 }, dis);
		}
	}
	//���˻�
	for (auto addr : tmpObjArray.plane)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "���˻�[%.f]", obj.Distance);
			Draw::DrawLine(Data::dwSightX,0, out.x,out.y,&Draw::��ɫ,1);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 255,255,0,255 }, dis);
		}
	}
	//����
	for (auto addr : tmpObjArray.boom)
	{
		obj.Object = addr;
		obj.Vector3d = GameData::ReadVector3(ReadMem<ULONG64>(obj.Object + m_RootComponent), m_Vector3);
		obj.ObjectId = ReadMem<DWORD>(obj.Object + m_ObjectId);
		obj.ObjectType = GameAlgorithm::GetNameFromFName(obj.ObjectId, Data::g_Ue4Engine.pGname);
		obj.Distance = GameData::Get3dDistance(Data::g_LocalPlayer.Vector3d, obj.Vector3d, 100);
		if (obj.Distance > 300)
			continue;
		obj.ObjectRealName = GameData::GetObjectName(obj.Object);
		if (StrStrIA(obj.ObjectType.c_str(), _xor_("Claymore")) != NULL)
			obj.ObjectRealName = "��������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("ImprovisedClaymore")) != NULL)
			obj.ObjectRealName = "������������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("Mine_01")) != NULL)
			obj.ObjectRealName = "��������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("Mine_02")) != NULL)
			obj.ObjectRealName = "С�ͷ�������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("PromTrap")) != NULL)
			obj.ObjectRealName = "����������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("StakePitTrap")) != NULL)
			obj.ObjectRealName = "׮������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("PressureCookerBomb")) != NULL)
			obj.ObjectRealName = "ѹ����ը��";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("CartridgeTrap")) != NULL)
			obj.ObjectRealName = "��������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("BarbedSpikeTrap")) != NULL)
			obj.ObjectRealName = "��������";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("Sensor_Detonator")) != NULL)
			obj.ObjectRealName = "��Ӧ�׹�";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("ImprovisedMine")) != NULL)
			obj.ObjectRealName = "ƿ��ը��";
		else if (StrStrIA(obj.ObjectType.c_str(), _xor_("PipeBomb")) != NULL)
			obj.ObjectRealName = "�����׹�";
		if (obj.ObjectRealName.empty())
			continue;
		if (GameData::WorldToScreen_2D(Data::g_Ue4Engine.ViewWorld, obj.Vector3d, &out))
		{
			sprintf(dis, "%s[%.f]",obj.ObjectRealName.c_str(), obj.Distance);
			Draw::DrawStrokeText(out.x, out.y, new RGBA{ 0,43,128,255 }, dis);
		}
	}
}

void GameMain::DrawBone(ULONG64 ObjectMesh, Matrix m, RGBA* Color,int width)
{
	//--��������
	Vector3 ͷ��; GameData::GetBonePosition(ObjectMesh, &ͷ��,80);
	Vector3 ����; GameData::GetBonePosition(ObjectMesh,&����,64);
	Vector3 ����;GameData::GetBonePosition(ObjectMesh,&����,41);
	Vector3 ������;GameData::GetBonePosition(ObjectMesh,&������,40);
	Vector3 ����;GameData::GetBonePosition(ObjectMesh,&����,39);
	Vector3 �Ҽ��;GameData::GetBonePosition(ObjectMesh,&�Ҽ��,43);
	Vector3 ������;GameData::GetBonePosition(ObjectMesh,&������,44);
	Vector3 ����;GameData::GetBonePosition(ObjectMesh,&����,45);
	Vector3 �Ų�;GameData::GetBonePosition(ObjectMesh,&�Ų�,1);
	Vector3 ��ƨ��;GameData::GetBonePosition(ObjectMesh,&��ƨ��,2);
	Vector3 ��ϥ��;GameData::GetBonePosition(ObjectMesh,&��ϥ��,3);
	Vector3 ���;GameData::GetBonePosition(ObjectMesh,&���,4);
	Vector3 ��ƨ��;GameData::GetBonePosition(ObjectMesh,&��ƨ��,15);
	Vector3 ��ϥ��;GameData::GetBonePosition(ObjectMesh,&��ϥ��,10);
	Vector3 �ҽ�;GameData::GetBonePosition(ObjectMesh,&�ҽ�,11);

	Vector2 Bone_ͷ��; GameData::WorldToScreen_2D(m, ͷ��, &Bone_ͷ��);
	Vector2 Bone_����; GameData::WorldToScreen_2D(m, ����, &Bone_����);
	Vector2 Bone_����; GameData::WorldToScreen_2D(m, ����, &Bone_����);
	Vector2 Bone_������; GameData::WorldToScreen_2D(m, ������, &Bone_������);
	Vector2 Bone_����; GameData::WorldToScreen_2D(m, ����, &Bone_����);
	Vector2 Bone_�Ҽ��; GameData::WorldToScreen_2D(m, �Ҽ��, &Bone_�Ҽ��);
	Vector2 Bone_������; GameData::WorldToScreen_2D(m, ������, &Bone_������);
	Vector2 Bone_����; GameData::WorldToScreen_2D(m, ����, &Bone_����);
	Vector2 Bone_�Ź�; GameData::WorldToScreen_2D(m, �Ų�, &Bone_�Ź�);
	Vector2 Bone_��ƨ��; GameData::WorldToScreen_2D(m, ��ƨ��, &Bone_��ƨ��);
	Vector2 Bone_��ϥ��; GameData::WorldToScreen_2D(m, ��ϥ��, &Bone_��ϥ��);
	Vector2 Bone_���; GameData::WorldToScreen_2D(m, ���, &Bone_���);
	Vector2 Bone_��ƨ��; GameData::WorldToScreen_2D(m, ��ƨ��, &Bone_��ƨ��);
	Vector2 Bone_��ϥ��; GameData::WorldToScreen_2D(m, ��ϥ��, &Bone_��ϥ��);
	Vector2 Bone_�ҽ�; GameData::WorldToScreen_2D(m, �ҽ�, &Bone_�ҽ�);
	if (Bone_ͷ�� != Vector2() &&
		Bone_���� != Vector2() &&
		Bone_���� != Vector2() &&
		Bone_������ != Vector2() &&
		Bone_���� != Vector2() &&
		Bone_�Ҽ�� != Vector2() &&
		Bone_������ != Vector2() &&
		Bone_���� != Vector2() &&
		Bone_�Ź� != Vector2() &&
		Bone_��ƨ�� != Vector2() &&
		Bone_��ϥ�� != Vector2() &&
		Bone_��� != Vector2() &&
		Bone_��ƨ�� != Vector2() &&
		Bone_��ϥ�� != Vector2() &&
		Bone_�ҽ� != Vector2())
	{

		Draw::DrawLine(Bone_ͷ��.x, Bone_ͷ��.y, Bone_����.x, Bone_����.y, Color, width);
		Draw::DrawLine(Bone_����.x, Bone_����.y, Bone_����.x, Bone_����.y, Color, width);

		Draw::DrawLine(Bone_����.x, Bone_����.y, Bone_������.x, Bone_������.y, Color, width);
		Draw::DrawLine(Bone_������.x, Bone_������.y, Bone_����.x, Bone_����.y, Color, width);

		Draw::DrawLine(Bone_����.x, Bone_����.y, Bone_�Ҽ��.x, Bone_�Ҽ��.y, Color, width);
		Draw::DrawLine(Bone_�Ҽ��.x, Bone_�Ҽ��.y, Bone_������.x, Bone_������.y, Color, width);
		Draw::DrawLine(Bone_������.x, Bone_������.y, Bone_����.x, Bone_����.y, Color, width);

		Draw::DrawLine(Bone_����.x, Bone_����.y, Bone_�Ź�.x, Bone_�Ź�.y, Color, width);

		Draw::DrawLine(Bone_�Ź�.x, Bone_�Ź�.y, Bone_��ƨ��.x, Bone_��ƨ��.y, Color, width);
		Draw::DrawLine(Bone_��ƨ��.x, Bone_��ƨ��.y, Bone_��ϥ��.x, Bone_��ϥ��.y, Color, width);
		Draw::DrawLine(Bone_��ϥ��.x, Bone_��ϥ��.y, Bone_���.x, Bone_���.y, Color, width);

		Draw::DrawLine(Bone_�Ź�.x, Bone_�Ź�.y, Bone_��ƨ��.x, Bone_��ƨ��.y, Color, width);
		Draw::DrawLine(Bone_��ƨ��.x, Bone_��ƨ��.y, Bone_��ϥ��.x, Bone_��ϥ��.y, Color, width);
		Draw::DrawLine(Bone_��ϥ��.x, Bone_��ϥ��.y, Bone_�ҽ�.x, Bone_�ҽ�.y, Color, width);
	}


}
