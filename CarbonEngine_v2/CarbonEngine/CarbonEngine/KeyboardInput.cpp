#include "KeyboardInput.h"

void ProcessKeystroke(WPARAM keyCode, LPARAM prevState)
{
	unsigned int key = keyCode;
	int pState = ((1 << 30) & prevState) == 0;
	char msg[100];
	sprintf_s(msg, 100, "Previous State: %d\n", pState);
	OutputDebugStringA(msg);

	switch (key)
	{
	case A_KEY:
	{
		OutputDebugStringA("A\n");
	}break;
	case D_KEY:
	{
		OutputDebugStringA("D\n");
	}break;
	case S_KEY:
	{
		OutputDebugStringA("S\n");
	}break;
	case W_KEY:
	{
		OutputDebugStringA("W\n");
	}break;
	case SPACE_KEY:
	{
		OutputDebugStringA("SPACE\n");
	}break;
	case VK_LEFT:
	{
		OutputDebugStringA("LEFT\n");
	}break;
	case VK_RIGHT:
	{
		OutputDebugStringA("RIGHT\n");
	}break;
	case VK_UP:
	{
		OutputDebugStringA("UP\n");
	}break;
	case VK_DOWN:
	{
		OutputDebugStringA("DOWN\n");
	}break;
	}

}