#ifndef SDLUTILS
#define SDLUTILS

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

/// <summary>
/// Initialisation of the rendering module.
/// </summary>
/// <returns></returns>
bool RenderInit();

/// <summary>
/// Dump errors in the console.
/// </summary>
/// <returns></returns>
string RenderErrorDetails();

/// <summary>
/// Exits rendering module.
/// </summary>
void RenderQuit();

#endif // !SDLUTILS
