#pragma once

#include <windows.h>
#include <stdio.h>

#define A_KEY 0x41
#define D_KEY 0x44
#define S_KEY 0x53
#define W_KEY 0x57
#define SPACE_KEY 0x20
/*
	Arrow keys are:
		VK_LEFT
		VK_DOWN
		VK_UP
		VK_RIGHT
*/


/**
 * @brief Process key up/down event and emit corresponding event
 * @param keyCode - Virtual key-code of the key
 * @param prevState - Prev state of the key (up or down bit)
*/
void ProcessKeystroke(WPARAM keyCode, LPARAM prevState);
