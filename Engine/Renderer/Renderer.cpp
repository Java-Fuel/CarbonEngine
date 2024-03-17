#include "Renderer.h"

Renderer::Renderer(Win32Platform *platform, int targetFps)
{
    this->_platform = platform;
    this->_logger = CarbonLogger::current();
    this->targetFps = targetFps;
    this->targetFrameTime = 1000 / this->targetFps;
    this->_runGame = false;

    xOffset = 0;
    yOffset = 10;
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
    run();
}

void Renderer::stop()
{
    _runGame = false;
}

/** Private Methods **/
void Renderer::run()
{
    unsigned int prevFrameStart = _platform->getTick();
    while(_runGame)
    {
        unsigned int currentFrameStart = _platform->getTick();
        double deltaTime = (currentFrameStart - prevFrameStart) / 1000;
        prevFrameStart = currentFrameStart;
        processInput();
        update(deltaTime);
        fixedUpdate();

        xOffset + (deltaTime * 1);
        yOffset + (deltaTime * 1);

    }
}

void Renderer::processInput()
{
    _platform->Win32PollEvents();
}

void Renderer::update(double deltaTime)
{
    renderPattern(deltaTime); 

    _platform->Win32Draw();
}

void Renderer::fixedUpdate()
{
    // TODO: implement
    return;
}

void Renderer::renderPattern(double deltaTime)
{
    u32 stride = _platform->bufferWidth * _platform->bytesPerPixel;
    u8* row = _platform->backBuffer;
    for(u32 Y = 0; Y < _platform->bufferHeight; ++Y)
    {   
        // Row of Pixel
        u8* pixel = row;
        for(u32 X = 0; X < _platform->bufferWidth; ++X)
        {
            // Set Blue
            *pixel = X + Y;
            ++pixel;

            // Set Green
            *pixel = (u8)(X + xOffset);
            ++pixel;

            // Set Red
            *pixel = 0;
            ++pixel;

            // Set Alpha
            *pixel = (u8)(Y + yOffset);
            ++pixel;
        }
        row += stride;
    }
}