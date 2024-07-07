#pragma once
#define _USE_MATH_DEFINES

#include <DSound.h>
#include <windows.h>
#include <cassert>
#include <cmath>
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
 * @brief Responsible for handling all audio playback code and configuration
 */
class AudioPlayback {
public:
	/**
	 * @brief Sample rate of the audio. Default is 48k
	 */
	int sampleRate = 48000;
private:
	LPDIRECTSOUNDBUFFER secondaryBuffer;
	int secondaryBufferSize;
	WAVEFORMATEX wavFormat;
	HINSTANCE dsoundDll;
	LPDIRECTSOUND dsound;
	/**
	 * @brief How many bytes in each sample of audio(2 channels)
	 */
	int bytesPerSample = 4;
	/**
	 * Number of channels to send output to (2 channels by default = LEFT & RIGHT)
	 */
	int numberOfChannels = 2;
	/**
	 * @brief // Number of bits per sample of audio (for 1 channel)
	 */
	int bitsPerSample = 16;
	/**
	 * @brief The size of the buffer in seconds (will be converted to byte size based on 
	 * the number of seconds of audio wanting to be played)
	 */
	int bufferSizeSeconds = 1;
	/**
	 * @brief Running count of samples we have written to in our secondary buffer. Used to 'unwrap' the sound buffer
	 * and make writing to it easier to implement.
	 */
	unsigned int runningSampleIndex = 0;
	bool soundIsPlaying = false;

public:
	AudioPlayback() = default;

	/**
	 * @brief Initialize DirectSound, audio devices, and buffers
	 * @param handle Window Handle
	 * @param bufferLengthInSeconds The number of seconds of audio to be stored in secondary buffer
	 */
	AudioPlayback(HWND handle, int bufferLengthInSeconds);

	/**
	 * @brief Play sample square wave in middle C for debugging purposes
	 */
	void PlaySample();

	/**
	 * @brief Create square wave to play as a debug sample
	 */
	void CreateSquareWave(bool fillBuffer = false);

private:
	void CreatePrimaryBuffer(HWND handle);
	void CreateSecondaryBuffer(HWND handle);
};