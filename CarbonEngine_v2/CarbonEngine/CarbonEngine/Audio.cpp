#include "Audio.h"


/* -- DirectSound DLL Fallback Functions -- */
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


/* -- AudioPlayback Implementation -- */
AudioPlayback::AudioPlayback(HWND handle, int bufferLengthInSeconds)
{
	this->bufferSizeSeconds = bufferLengthInSeconds;
	this->secondaryBufferSize = bufferSizeSeconds * sampleRate * bytesPerSample;

	// Load DLL
	this->dsoundDll = LoadLibrary(DSOUND_DLL_NAME);
	if (this->dsoundDll != NULL)
	{
		// Load DirectSoundCreate function from DLL
		dsound_create_com* create_func = (dsound_create_com*)GetProcAddress(this->dsoundDll, "DirectSoundCreate");
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

	this->dsound;
	HRESULT dsoundCreateResult = DSoundCreate(NULL, &this->dsound, NULL);
	if (!SUCCEEDED(dsoundCreateResult))
	{
		LogError("Could not create IDirectSound object.\n");
		return;
	}

	// Set cooperative level
	HRESULT cooperativeResult = this->dsound->SetCooperativeLevel(handle, DSSCL_PRIORITY);
	if (!SUCCEEDED(cooperativeResult))
	{
		LogError("Could not create prumary sound buffer.\n");
		LogWinError();
		return;
	}

	// Create WAV Formate
	this->wavFormat = {};
	this->wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	this->wavFormat.nChannels = this->numberOfChannels;
	this->wavFormat.nSamplesPerSec = this->sampleRate;
	this->wavFormat.wBitsPerSample = this->bitsPerSample;
	this->wavFormat.nBlockAlign = (this->wavFormat.nChannels * this->wavFormat.wBitsPerSample) / 8;
	this->wavFormat.cbSize = 0;
	this->wavFormat.nAvgBytesPerSec = this->wavFormat.nSamplesPerSec * this->wavFormat.nBlockAlign;

	CreatePrimaryBuffer(handle);
	CreateSecondaryBuffer(handle);

}

void AudioPlayback::PlaySample()
{

}

/* -- Private Methods -- */

void AudioPlayback::CreatePrimaryBuffer(HWND handle)
{

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

	// Set PrimaryBuffer format
	HRESULT setFormatResult = primaryBuffer->SetFormat(&wavFormat);
	if (!SUCCEEDED(setFormatResult))
	{
		LogError("Could not set format of primary sound buffer.\n");
		LogWinError();
		return;
	}
}

void AudioPlayback::CreateSecondaryBuffer(HWND handle)
{
	// Create Secondary Buffer 
	DSBUFFERDESC secondaryBufferDesc = {};
	secondaryBufferDesc.dwSize = sizeof(secondaryBufferDesc);
	secondaryBufferDesc.dwFlags = 0;
	secondaryBufferDesc.dwBufferBytes = secondaryBufferSize;
	secondaryBufferDesc.lpwfxFormat = &wavFormat;

	secondaryBufferSize = secondaryBufferSize;
	HRESULT result = dsound->CreateSoundBuffer(&secondaryBufferDesc, &secondaryBuffer, 0);
	if (!SUCCEEDED(result))
	{
		LogError("Could not create secondary sound buffer.\n");
		LogWinError();
		return;
	}
}


void AudioPlayback::CreateSquareWave()
{
	DWORD byteToLock = ; // The byte in the buffer to start locking so we can write new audio (after write buffer)
	DWORD bytesToWrite = ; // How many bytes we intend to write to the buffer. DSound needs this so it can determine how many regions to return to us
	LPVOID audioRegion1;
	DWORD audioRegionSize1;
	LPVOID audioRegion2;
	DWORD audioRegionSize2;

	HRESULT lockResult = secondaryBuffer->Lock(
		byteToLock, bytesToWrite,
		&audioRegion1, &audioRegionSize1,
		&audioRegion2, &audioRegionSize2, 0
	);

	if (!SUCCEEDED(lockResult))
	{
		LogError("Could not lock secondary buffer.");
		LogWinError();
	}

	// Enusre regions are a proper multiple of sample size (2 channels, 2 bytes each = 4 bytes)
	assert(audioRegionSize1 % 4 == 0);
	assert(audioRegionSize2 % 4 == 0);

	int middleC = 261;
	int samplesPerCycle = sampleRate / middleC;
	int halfSpC = samplesPerCycle / 2;
	int volumeLevel = 3000;
	int squareWavCount = 0;

	// Fill region 1 with samples
	int sampleCount1 = audioRegionSize1 / bytesPerSample;
	short* sampleOut = (short*)audioRegion1;
	for (int sampleIndex = 0; sampleIndex < sampleCount1; sampleIndex++)
	{
		if (!squareWavCount)
		{
			squareWavCount = samplesPerCycle;
		}
		int sampleValue = (squareWavCount > halfSpC) ? volumeLevel : -volumeLevel;
		*sampleOut++ = sampleValue;
		*sampleOut++ = sampleValue;
		squareWavCount--;
	}

	// Fill region 2 with samples
	int sampleCount2 = audioRegionSize2 / bytesPerSample;
	sampleOut = (short*)audioRegion2;
	for (int sampleIndex = 0; sampleIndex < sampleCount2; sampleIndex++)
	{
		if (!squareWavCount)
		{
			squareWavCount = samplesPerCycle;
		}
		int sampleValue = (squareWavCount > halfSpC) ? volumeLevel : -volumeLevel;
		*sampleOut++ = sampleValue;
		*sampleOut++ = sampleValue;
		squareWavCount--;
	}
}
