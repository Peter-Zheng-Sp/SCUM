#include "Read.h"

void ReadVirtual(LPVOID src, LPVOID dest, size_t sz)
{
	if (IsBadReadPtr(src, sz))
	{
		RtlZeroMemory(dest, sz);
		return;
	}
	RtlCopyMemory(dest, src, sz);
}
void WriteVirtual(LPVOID src, LPVOID dest, size_t sz)
{
	if (IsBadReadPtr(src, sz))
		return;
	DWORD oldProtect = 0;
	VirtualProtect(src, sz, PAGE_EXECUTE_READWRITE, &oldProtect);
	RtlCopyMemory(src, dest, sz);
	VirtualProtect(src, sz, oldProtect, &oldProtect);
}
