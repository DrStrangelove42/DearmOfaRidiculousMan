#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "config.h"

extern TTF_Font* FONT;
extern int FONTSIZE;

void renderSleep(unsigned int ms);
bool renderInit();
std::string renderErrorDetails();
SDL_Window* renderCreateWindow();
void renderQuit();
#endif