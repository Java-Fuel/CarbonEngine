#pragma once
/**
* NOTES:
*		- This method of checking for controllers plugged in at the start could cause issues if a controller is plugged
*			in after the engine is started. 
*		- TODO: Find a better way to periodically check which controllers are plugged in
*/

/**
* This file contains method definitions for polling and processing
* controller input. 
*/

#include "CarbonLogger.h"	

#include <winerror.h>
#include <libloaderapi.h>
#include <Xinput.h>
#include <vector>

#define MAX_CONTROLLER_COUNT 3
#define BUTTON_A 0x1000
#define BUTTON_B 0x2000
#define BUTTON_X 0x4000
#define BUTTON_Y 0x8000

#define XINPUT_DLL "xinput1_3.dll"

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state); 

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);

/**
 * @brief Initialize the XInput methods by loading the proper functions
 * from DLLs.
*/
void initXInput(void);

/**
	* @brief Poll computer for controller/gamepad state
*/
void PollControllerInput();

/** 
 * @brief Vibrate controller
 * @param leftMotorSpeed vibration amount for left controller motor (0 - INT_MAX)
 * @param rightMotorSpeed vibration amount for right controller motor (0 - INT_MAX)
*/
void RumbleController(int leftMotorSpeed, int rightMotorSpeed);