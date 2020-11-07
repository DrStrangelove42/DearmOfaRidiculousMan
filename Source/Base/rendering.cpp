#include "rendering.h"

void renderSleep(unsigned int ms)
{
	SDL_Delay(ms);
}

bool renderInit()
{
	return SDL_Init(SDL_INIT_VIDEO) == 0;
}

void renderQuit()
{
	SDL_Quit();
}

std::string renderErrorDetails()
{
	std::string ret(SDL_GetError());
	return ret;
}

SDL_Window* renderCreateWindow()
{
	return SDL_CreateWindow("DOARM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SZ_SCREENWIDTH, SZ_SCREENHEIGHT, SDL_WINDOW_SHOWN);
}