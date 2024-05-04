#pragma once

#include "../Platform/Win32Platform.h"
#include "../Utils/CarbonLogger.h"
#include <string>

class Renderer
{
public:
    int targetFps;
    int targetFrameTime;

private:
    bool _runGame;
    Win32Platform *_platform;
    CarbonLogger *_logger;

    // TODO: Debug only, delete when done
    int xOffset;
    int yOffset;  

public:
    Renderer(Win32Platform* platform, int targetFps = 60);
    ~Renderer();
    void start();
    void stop();

private:
    void run();
    void update(double deltaTime);
    void fixedUpdate();
    void processInput();

    // TODO: Debug only, remove when done testing
    void renderPattern(double deltaTime);
};