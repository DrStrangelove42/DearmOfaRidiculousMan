#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <string>
#include "config.h"

void renderSleep(unsigned int ms);
bool renderInit();
std::string renderErrorDetails();
SDL_Window* renderCreateWindow();
void renderQuit();
#endif