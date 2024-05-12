#pragma once
#include <DSound.h>
#include <windows.h>
#include "CarbonLogger.h"

/*
 NOTE (joe): Using DirectSound to follow along with Casey's videos. Need to upgrade to WASAPI once comfortable with DirectSound
 concepts. 
*/

#define DSOUND_DLL_NAME "dsound.dll"


/*
* TODO:Function pointers for:
*	- CreateSoundBuffer
*	- DirectSoundCreate8
*	- Lock
*	- Unlock
*/
/**
* Function pointer for DirectSoundCreate method
*/
#define DSOUND_CREATE(name) HRESULT WINAPI name(LPGUID lpguid, LPDIRECTSOUND* ppDS, LPUNKNOWN pUnkOuter)
typedef DSOUND_CREATE(dsound_create_com);

/**
* Function pointer for DirectSound CreateSoundBuffer method
*/
#define DSOUND_CREATE_SOUND_BUFFER(name) HRESULT name(LPCDSBUFFERDESC pcDSBufferDesc, LPDIRECTSOUNDBUFFER* ppDSBuffer, LPUNKNOWN pUnkOuter)
typedef DSOUND_CREATE_SOUND_BUFFER(dsound_create_sound_buffer);


/**
 * @brief Load DirectSound DLL and initialize DirectSound hardware
*/
void DSoundInitialize();
