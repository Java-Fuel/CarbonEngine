#pragma once
#include "Win32Platform.h"
#include "CarbonLogger.h"
#include "Defines.h"
#include "ControllerInput.h"
#include "PlatformEventManager.h"
#include "Audio.h"
#include "Dsound.h"

#include <string>


class CAPI Renderer
{
public:
  int targetFps;
  int targetFrameTime;

private:
  bool _runGame;
  Win32Platform* _platform;

  // TODO: Debug only, delete when done
  float xOffset;
  float yOffset;
  int squareWavCounter; 

public:
  Renderer(Win32Platform* platform, int targetFps = 60);
  ~Renderer();
  void start();
  void stop();

private:
  void run();
  void update();
  void fixedUpdate();
  void processInput();
  void handleWindowClose(PlatformEventArgs* args);

  // TODO: Debug only, remove when done testing
  void renderPattern();
};