#include "Audio.h"


// Fallback implementation for DirectSoundCreate 
DSOUND_CREATE(DSoundCreateStub) 
{
	return (0);
}
static dsound_create_com* DSoundCreate = DSoundCreateStub;

// Fallback stub implementation for CreateSoundBuffer function
DSOUND_CREATE_SOUND_BUFFER(CreateSoundBufferStub)
{
	return (0);
}
static dsound_create_sound_buffer* DSoundCreateSoundBuffer = CreateSoundBufferStub;

static LPDIRECTSOUNDBUFFER secondaryBuffer;
static int secondaryBufferSize;
static unsigned int runningSampleIndex = 0;
static int bytesPerSample = 4; // 2 bytes for LEFT channel and 2 bytes for RIGHT channel

void DSoundInitialize(HWND windowHandle, int bufferSize)
{
	// Load DLL
	HINSTANCE dsoundDll = LoadLibrary(DSOUND_DLL_NAME);
	if (dsoundDll != NULL) 
	{
		// Load DirectSoundCreate function from DLL
		dsound_create_com* create_func = (dsound_create_com*)GetProcAddress(dsoundDll, "DirectSoundCreate");
		if (create_func == NULL)
		{
			LogError("Could not load DSoundCreate function.\n");
		}
		DSoundCreate = create_func;
		LogInfo("Direct Sound loaded successfully!\n");
	}
	else
	{
		LogError("Could not load DirectSound!\n");
		return;
	}

	// NOTE(Joe): Creating DirectSound object w/ default device here because we don't need it anywhere else in code
	
	LPDIRECTSOUND dsound;
	HRESULT dsoundCreateResult = DSoundCreate(NULL, &dsound, NULL);
	if (!SUCCEEDED(dsoundCreateResult))
	{
		LogError("Could not create IDirectSound object.\n");
		return;
	}

	// Set cooperative level
	HRESULT cooperativeResult = dsound->SetCooperativeLevel(windowHandle, DSSCL_PRIORITY);
	if (!SUCCEEDED(cooperativeResult))
	{
		LogError("Could not create prumary sound buffer.\n");
		LogWinError();
		return;
	}

	// Create primary buffer
	DSBUFFERDESC primaryBufferDesc = {};
	primaryBufferDesc.dwSize = sizeof(primaryBufferDesc);
	primaryBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	primaryBufferDesc.dwBufferBytes = 0;
	primaryBufferDesc.dwReserved = 0;
	primaryBufferDesc.lpwfxFormat = 0;
	primaryBufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	LPDIRECTSOUNDBUFFER primaryBuffer;
	HRESULT result = dsound->CreateSoundBuffer(&primaryBufferDesc, &primaryBuffer, 0);
	if (!SUCCEEDED(result))
	{
		LogError("Could not create prumary sound buffer.\n");
		LogWinError();
		return;
	}

	// Set format of primary buffer 
	WAVEFORMATEX wavFormat = {};
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	wavFormat.nChannels = 2;
	wavFormat.nSamplesPerSec = 48000;
	wavFormat.wBitsPerSample = 16;
	wavFormat.nBlockAlign = (wavFormat.nChannels * wavFormat.wBitsPerSample) / 8;
	wavFormat.cbSize = 0;
	wavFormat.nAvgBytesPerSec = wavFormat.nSamplesPerSec*wavFormat.nBlockAlign;
	HRESULT setFormatResult = primaryBuffer->SetFormat(&wavFormat);
	if (!SUCCEEDED(setFormatResult))
	{
		LogError("Could not set format of primary sound buffer.\n");
		LogWinError();
		return;
	}

	// Create Secondary Buffer 
	DSBUFFERDESC secondaryBufferDesc = {};
	secondaryBufferDesc.dwSize = sizeof(secondaryBufferDesc);
	secondaryBufferDesc.dwFlags = 0;
	secondaryBufferDesc.dwBufferBytes = bufferSize;
	secondaryBufferDesc.lpwfxFormat = &wavFormat;

	secondaryBufferSize = bufferSize;
	result = dsound->CreateSoundBuffer(&secondaryBufferDesc, &secondaryBuffer, 0);
	if (!SUCCEEDED(result))
	{
		LogError("Could not create secondary sound buffer.\n");
		LogWinError();
		return;
	}

}



void PlaySquareWave() 
{
	DWORD playCursor; 
	DWORD writeCursor;
	

	if (SUCCEEDED(secondaryBuffer->GetCurrentPosition(&playCursor, &writeCursor)))
	{
		VOID* region1;
		DWORD region1Size;
		VOID* region2;
		DWORD region2Size;
		DWORD byteToLock = runningSampleIndex * bytesPerSample % secondaryBufferSize;
		DWORD byteToWrite;
		if (byteToLock > playCursor)
		{
			byteToWrite = secondaryBufferSize - byteToLock;
			byteToWrite += playCursor;
		} else
		{
			byteToWrite = playCursor - byteToLock;
		}

		HRESULT lockResult = secondaryBuffer->Lock(
			byteToLock, byteToWrite, &region1,
			&region1Size, &region2, &region2Size, 0
		);

		if (SUCCEEDED(lockResult))
		{
			int hz = 256;
			int sampleSize = 48000;
			int squareWavePeriod = sampleSize / hz;
			int halfSquareWavePeriod = squareWavePeriod / 2;
			DWORD reqion1SampleCount = region1Size / bytesPerSample;
			short* sampleOut = (short*)region1;
			for (DWORD sampleIndex = 0; sampleIndex < reqion1SampleCount; sampleIndex++)
			{
				short sampleValue = ((runningSampleIndex++ / halfSquareWavePeriod) % 2) ? 1000 : -1000;
				*sampleOut++ = sampleValue;
				*sampleOut++ = sampleValue;
			}
			sampleOut = (short*)region2;
			DWORD region2SampleCount = region2Size / bytesPerSample;
			for (DWORD sampleIndex = 0; sampleIndex < region2SampleCount; sampleIndex++)
			{
				short sampleValue = ((runningSampleIndex++ / halfSquareWavePeriod) % 2) ? 1000 : -1000;
				*sampleOut++ = sampleValue;
				*sampleOut++ = sampleValue;
			}

			secondaryBuffer->Unlock(&region1, region1Size, &region2, region2Size);
		}
	}
}

void StartPlayback()
{
	secondaryBuffer->Play(
		0,
		0,
		DSBPLAY_LOOPING
	);
}