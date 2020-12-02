#include "rendering.h"

TTF_Font* FONT;
int FONTSIZE = 16;

void renderSleep(unsigned int ms)
{
	SDL_Delay(ms);
}

bool renderInit()
{
	if (TTF_Init() == -1)
		return false;

	FONT = TTF_OpenFont("Res/ibm.ttf", FONTSIZE);
#ifdef WIN6
	SetProcessDPIAware();
#endif
	return SDL_Init(SDL_INIT_VIDEO) == 0;
}

void renderQuit()
{
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
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