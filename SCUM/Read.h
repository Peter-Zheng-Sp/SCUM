#pragma once
#include <Windows.h>

void ReadVirtual(LPVOID src, LPVOID dest, size_t sz);

void WriteVirtual(LPVOID src, LPVOID dest, size_t sz);

template <typename DataType> DataType ReadMem(ULONG64 address)
{
	DataType pBuffer;
	ReadVirtual((PVOID)address, &pBuffer, sizeof(DataType));
	return pBuffer;
}
template <typename DataType> VOID WriteMem(ULONG64 address, DataType value)
{
	WriteVirtual((PVOID)address, &value, sizeof(DataType));
}