#include <Windows.h>

char* CreateBuffer(int size)
{
	char* buffer = new char[size];

	ZeroMemory(buffer, size);

	return buffer;
}