#include "RenderContext.h"
#include "Texture.h"

RenderContext::RenderContext(Window& window)
{
	renderer = window.getRenderer();

	if (NULL == renderer)
	{
		throw runtime_error(SDL_GetError());
	}
}

RenderContext::~RenderContext()
{
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
}

void RenderContext::clear()
{
	changeColor(0x000000ff);
	SDL_RenderClear(renderer);
}

void RenderContext::doRender(SDL_Texture* t,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect,
	const double angle,
	const SDL_Point* center,
	const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip);
}

void RenderContext::update()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderContext::fromSurface(SDL_Surface* s)
{
	return SDL_CreateTextureFromSurface(renderer, s);
}

void RenderContext::changeColor(int color)
{
	if (0 != SDL_SetRenderDrawColor(renderer, (unsigned char)(color >> 24),
		(unsigned char)(color >> 16),
		(unsigned char)(color >> 8),
		(unsigned char)(color)))
		throw runtime_error(SDL_GetError());
}

void RenderContext::drawRectangle(int x, int y, int w, int h, bool fill)
{
	SDL_Rect rect = { x, y, w, h };
	if (fill)
		SDL_RenderFillRect(renderer, &rect);
	else
		SDL_RenderDrawRect(renderer, &rect);
}

void RenderContext::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


/*Static functions*/


void RenderContext::RenderSleep(unsigned int ms)
{
	SDL_Delay(ms);
}

bool RenderContext::RenderInit()
{
	if (TTF_Init() == -1)
		return false;

	FONTSIZE = 16;

	FONT = TTF_OpenFont("Res/ibm.ttf", FONTSIZE);
#ifdef WIN6
	SetProcessDPIAware();
#endif
	return SDL_Init(SDL_INIT_VIDEO) == 0;
}

void RenderContext::RenderQuit()
{
	FreeTextures();
	TTF_CloseFont(FONT);
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

string RenderContext::RenderErrorDetails()
{
	std::string ret(SDL_GetError());
	return ret;
}

/*Utils former code moved here*/
/*
Loads the texture with the specified identifier.
*/
Texture* RenderContext::LoadTexture(string id)
{
	if (textures.find(id) == textures.end())
		textures[id] = new Texture(*this, id);

	return textures[id];
}

Texture* RenderContext::LoadString(string text, int color)
{
	string id = "text." + to_string(color) + "/" + text;
	if (textures.find(id) == textures.end())
	{
		textures[id] = LoadVolatileString(text, color);
	}

	return textures[id];
}

TTF_Font* RenderContext::FONT;
int RenderContext::FONTSIZE;
unordered_map<string, Texture*> RenderContext::textures;

Texture* RenderContext::LoadVolatileString(string text, int color)
{
	SDL_Color c = { (unsigned char)(color >> 24),
							(unsigned char)(color >> 16),
							(unsigned char)(color >> 8),
							(unsigned char)(color) };

	SDL_Surface* s = TTF_RenderText_Solid(FONT, text.c_str(), c);
	SDL_Texture* t = this->fromSurface(s);
	SDL_FreeSurface(s);

	int w, h;
	if (TTF_SizeText(FONT, text.c_str(), &w, &h))
	{
		cout << TTF_GetError() << endl;
		return NULL;
	}

	return new Texture(t, w, h);
}

void RenderContext::FreeTextures()
{
	for (auto& entry : textures)
	{
		//if (DEBUG_MODE)
		//	cout << "Freeing " << entry.first << " :: " << entry.second->getHeight() << "*" << entry.second->getWidth() << endl;
		delete entry.second;
	}
	textures.clear();
}