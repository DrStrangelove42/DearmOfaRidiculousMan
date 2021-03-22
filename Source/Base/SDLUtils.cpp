#include "SDLUtils.h"

bool RenderInit()
{
	if (TTF_Init() == -1)
		return false;
	
	return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0;
}

void RenderQuit()
{
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Quit();
}

string RenderErrorDetails()
{
	std::string ret(SDL_GetError());
	return ret;
}