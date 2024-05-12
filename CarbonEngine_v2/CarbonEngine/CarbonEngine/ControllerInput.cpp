#include "ControllerInput.h"


// TODO (joe): Clean up global vars
static int controllerIndex = 0;
static int motorSpeed = 10000;


// Set default method for XInputGetState in case DLL is not found (prevents game crash)
X_INPUT_GET_STATE(XInputGetStateStub)
{
	return (ERROR_DEVICE_NOT_CONNECTED);
}
static x_input_get_state* XInputGetState_ = XInputGetStateStub;

// Set default method for XInputSetState in case DLL is not found (prevents game crash)
X_INPUT_SET_STATE(XInputSetStateStub)
{
	return (ERROR_DEVICE_NOT_CONNECTED);
}
static x_input_set_state* XInputSetState_ = XInputSetStateStub;

void initXInput(void)
{
	// TODO: Check if on Windows 8 b/c Windows 8 only supoprts XInput_1_4
	HMODULE xinputLib = LoadLibraryA(XINPUT_DLL);
	if (xinputLib == NULL)
	{
		LogError("Could not load XInput DLL.");
		return;
	}

	// Load XInputGetState function
	x_input_get_state* getStateFunc = (x_input_get_state*)GetProcAddress(xinputLib, "XInputGetState");
	if (getStateFunc != NULL)
	{
		LogInfo("Successfully loaded XInputGetState function!");
		XInputGetState_ = getStateFunc;
	}

	// Load XInputSetState Function
	x_input_set_state* setStateFunc = (x_input_set_state*)GetProcAddress(xinputLib, "XInputSetState");
	if (setStateFunc != NULL)
	{
		LogInfo("Successfully loaded XInputSetState function!");
		XInputSetState_ = setStateFunc;
	}
}

void PollControllerInput()
{

	DWORD dwResult;

	// Only check ports where controller was found 
	for (int userIndex = 0; userIndex <= MAX_CONTROLLER_COUNT; userIndex++)
	{
		XINPUT_STATE state;
		if (XInputGetState_(userIndex, &state) == ERROR_SUCCESS)
		{
			controllerIndex = userIndex;
			XINPUT_GAMEPAD gamepad = state.Gamepad;
			if ((gamepad.wButtons & BUTTON_A) == BUTTON_A)
			{
				LogInfo("'A' Button Pressed!");
				motorSpeed += 1000;
			}

			if ((gamepad.wButtons & BUTTON_B) == BUTTON_B)
			{
				LogInfo("'B' Button Pressed!");
				motorSpeed -= 1000;
			}
		}
	}
}

void RumbleController(int leftMotorSpeed, int rightMotorSpeed)
{
	XINPUT_VIBRATION vibration;

	if (leftMotorSpeed == 0 && rightMotorSpeed == 0)
	{
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;
	}
	else
	{
		vibration.wLeftMotorSpeed = motorSpeed;
		vibration.wRightMotorSpeed = motorSpeed;
	}


	DWORD rumbleResult = XInputSetState_(controllerIndex, &vibration);
	if (rumbleResult == ERROR_DEVICE_NOT_CONNECTED)
	{
		LogError("Could not find controller to vibrate.");
	}
}