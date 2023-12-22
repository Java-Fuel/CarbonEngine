
#include <stdio.h>
#include "Math.hpp"
#include "Platform.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"

using CarbonMath::Math;
using CarbonPlatform::Platform;
using CarbonRenderer::Renderer;
using Logging::Logger;

int main(int argc, char* argv[])
{
  Math m;
  int sum = m.add(1, 2);

  Platform p;
  p.InitWindow();

  Renderer r;
  r.Update();

  Logger::Info("Testing the console logger\n");

  printf("Hello Carbon Engine!\n");
  printf("Adding Result: %d\n", sum);
  return 0;
}