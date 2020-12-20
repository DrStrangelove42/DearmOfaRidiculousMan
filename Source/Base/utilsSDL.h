#ifndef UTILS_SDL_H
#define UTILS_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "game.h"
#ifdef WIN6
#include <Windows.h>
#undef LoadString
#endif

extern TTF_Font* FONT;
extern int FONTSIZE;

/// <summary>
/// Stops during ms milliseconds.
/// </summary>
/// <param name="ms">The delay</param>
void RenderSleep(unsigned int ms);

/// <summary>
/// Initialisation of the rendering module
/// </summary>
/// <returns></returns>
bool RenderInit();

/// <summary>
/// Dump errors in the console.
/// </summary>
/// <returns></returns>
string RenderErrorDetails();

/// <summary>
/// Exits rendering module
/// </summary>
void RenderQuit();
/*End of SDL-Specific zone*/
#endif
