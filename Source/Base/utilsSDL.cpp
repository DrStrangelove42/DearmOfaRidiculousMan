#include "utilsSDL.h"

TTF_Font* FONT;
int FONTSIZE = 16;

void RenderSleep(unsigned int ms)
{
	SDL_Delay(ms);
}

bool RenderInit()
{
	if (TTF_Init() == -1)
		return false;

	FONT = TTF_OpenFont("Res/ibm.ttf", FONTSIZE);
#ifdef WIN6
	SetProcessDPIAware();
#endif
	return SDL_Init(SDL_INIT_VIDEO) == 0;
}

void RenderQuit()
{
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

string RenderErrorDetails()
{
	std::string ret(SDL_GetError());
	return ret;
}