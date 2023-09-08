#include"Data.h"
ULONG64 Data::BaseModule = NULL;
HWND Data::hGame = NULL;
DWORD Data::dwSightX = NULL;
DWORD Data::dwSightY = NULL;
UE4Engine<ULONG64> Data::g_Ue4Engine;
Object<ULONG64> Data::g_LocalPlayer;
ObjArray Data::g_ObjArray;
BOOL Data::isGameMenu=false;
DWORD Data::MagicBulletValue=0;
Option Data::op;
AimBot Data::aimBot[2];