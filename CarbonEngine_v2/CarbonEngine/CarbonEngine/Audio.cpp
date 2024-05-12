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


void DSoundInitialize() 
{
	// Load DLL
	HINSTANCE dsoundDll = LoadLibrary(DSOUND_DLL_NAME);
	if (dsoundDll == NULL) 
	{
		LogError("Could not load DirectSound!\n");
	}

	LogInfo("Direct Sound loaded successfully!\n");

	// Load DirectSoundCreate function from DLL
	dsound_create_com* create_func = (dsound_create_com*)GetProcAddress(dsoundDll, "DirectSoundCreate");
	if (create_func == NULL)
	{
		LogError("Could not load DSoundCreate function.\n");
	}
	DSoundCreate = create_func;

	// NOTE(Joe): Creating DirectSound object w/ default device here because we don't need it anywhere else in code
	// TODO(Joe): Need to SetCooperativeLevel b/c creating a PrimaryBuffer without doing this results in failure
	LPDIRECTSOUND dsound;
	HRESULT dsoundCreateResult = DSoundCreate(NULL, &dsound, NULL);
	if (!SUCCEEDED(dsoundCreateResult))
	{
		LogError("Could not create IDirectSound object.\n");
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
	}

	// Create Secondary Buffer 

}