#include "Renderer.h"

Renderer::Renderer(Win32Platform* platform, int targetFps)
{
	this->_platform = platform;
	this->targetFps = targetFps;
	this->targetFrameTime = 1000 / this->targetFps;
	this->_runGame = false;
	xOffset = 0;
	yOffset = 10;
	squareWavCounter = 0;

	this->_audio = AudioPlayback(platform->windowHandle, 1);

	PlatformEventManager* current = PlatformEventManager::current();
	current->subscribe(PlatformEventType::WINDOW_CLOSE, new PlatformEventHandler<Renderer>(this, &Renderer::handleWindowClose));
}

Renderer::~Renderer()
{
	// TODO: Clean up resources if needed?
	// Nothing to do right now since platform pointer will get cleaned up when
	// Main closes

	return;
}

void Renderer::start()
{
	_runGame = true;
	initXInput();
	run();
}

void Renderer::stop()
{
	_runGame = false;
	// Stop Controller rumble if rumbling
	RumbleController(0, 0);
}

/** Private Methods **/
void Renderer::run()
{
	unsigned int prevFrameStart = _platform->getTick();

	while (_runGame)
	{
		unsigned int currentFrameStart = _platform->getTick();
		prevFrameStart = currentFrameStart;
		processInput();
		update();
		fixedUpdate();
		xOffset += 0.1;
		yOffset += 0.1;

	}
}

void Renderer::processInput()
{
	_platform->Win32PollEvents();
	PollControllerInput();
}

void Renderer::update()
{
	renderPattern();

	_platform->Win32Draw();
}

void Renderer::fixedUpdate()
{
	// TODO: implement
	return;
}

void Renderer::renderPattern()
{
	unsigned int stride = _platform->bufferWidth * _platform->bytesPerPixel;
	unsigned char* row = _platform->backBuffer;
	for (unsigned int Y = 0; Y < _platform->bufferHeight; ++Y)
	{
		// Row of Pixel
		unsigned char* pixel = row;
		for (unsigned int X = 0; X < _platform->bufferWidth; ++X)
		{
			// Set Blue
			*pixel = X + Y + (unsigned char)(yOffset + xOffset);;
			++pixel;

			// Set Green
			*pixel = (unsigned char)(X + xOffset);
			//_logger->info("Green Pixel: " + std::to_string(*pixel));
			++pixel;



			// Set Red
			*pixel = (unsigned char)(Y + yOffset);
			++pixel;

			// Set Alpha
			*pixel = 255;
			++pixel;
		}
		row += stride;
	}
}

void Renderer::handleWindowClose(PlatformEventArgs* args)
{
	stop();
}