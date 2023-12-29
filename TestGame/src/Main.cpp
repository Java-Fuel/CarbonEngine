#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <Math.hpp>
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  printf("Hello Carbon");

  // Testing SDL 
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Quit();
  return 0;
}