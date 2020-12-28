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

Texture* RenderContext::LoadText(string text, int color, int backColor, int width, int padding)
{
	string id = "mtext." + to_string(color) + "/" + text;
	if (textures.find(id) == textures.end())
	{
		text += " ";
		SDL_Color c = { (unsigned char)(color >> 24),
							   (unsigned char)(color >> 16),
							   (unsigned char)(color >> 8),
							   (unsigned char)(color) };
		
		

		SDL_Surface* textSurface = SDL_CreateRGBSurface(0, width, SZ_SCREENHEIGHT, 32, 0, 0, 0, 0);

		if (backColor != 0)
		{
			SDL_Color bc = { (unsigned char)(backColor >> 24),
										   (unsigned char)(backColor >> 16),
										   (unsigned char)(backColor >> 8),
										   (unsigned char)(backColor) };
			SDL_FillRect(textSurface, NULL, SDL_MapRGBA(textSurface->format, bc.r, bc.g, bc.b,bc.a));
		}

		SDL_Rect cur = { padding,padding,width,0 };
		SDL_Surface* s;
		int height = 2*padding;
		string word = "";
		for (int i = 0; i < text.size(); i++)
		{
			switch (text[i])
			{
			case ' ':
			case '\t':
			case '-':
				word += text[i];
				/*Fall through*/
			case '\n':
			case '\r':
				s = TTF_RenderText_Solid(FONT, word.c_str(), c);
				cur.h = s->h;
				cur.w = s->w;
				if (cur.x + cur.w + padding > width)
				{
					/*Line feed*/
					cur.x = padding;
					cur.y += cur.h;
					height += cur.h;
				}
				SDL_BlitSurface(s, NULL, textSurface, &cur);
				SDL_FreeSurface(s);
				cur.x += cur.w;
				word = "";
				if (text[i] == '\r' || text[i] == '\n')
				{
					/*Line feed*/
					cur.x = padding;
					cur.y += cur.h;
					height += cur.h;
				}
				break;
			default:
				word += text[i];
				break;
			}
		}
		height += cur.h;
		cur.x = cur.y = 0;
		cur.h = height;
		cur.w = width;
		/*Crop*/
		SDL_Surface* croppedTextSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
		SDL_BlitSurface(textSurface, &cur, croppedTextSurface, &cur);
		SDL_Texture* t = this->fromSurface(croppedTextSurface);
		SDL_FreeSurface(croppedTextSurface);
		SDL_FreeSurface(textSurface);
		textures[id] = new Texture(t, width, height);
	}

	return textures[id];
}

Texture* RenderContext::LoadText(string text, int color, int width)
{
	return LoadText(text, color, 0, width);
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