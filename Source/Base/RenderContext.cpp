#include "RenderContext.h"
#include "Texture.h"
#include "AnimatedTexture.h"


RenderContext::RenderContext(Window& window)
{
	renderer = window.getRenderer();
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
		cout << "Error blend mode" << endl;

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

SDL_Surface* RenderContext::createSurface(int w, int h, SDL_BlendMode blMode)
{
	uint32_t rmask, gmask, bmask, amask;
	MakeRGBAMasks(&rmask, &gmask, &bmask, &amask);
	SDL_Surface* ret = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	SDL_SetSurfaceBlendMode(ret, blMode);

	return ret;
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
		//cout << SDL_GetError() << endl;
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
	{
		if (id[0] == '*')
			textures[id] = new AnimatedTexture(*this, id.substr(1));
		else
			textures[id] = new Texture(*this, id);
	}

	return textures[id];
}

Texture* RenderContext::LoadString(string text, int color)
{
	string id = "text." + to_string(color) + "/" + text;
	if (textures.find(id) == textures.end())
	{
		textures[id] = LoadVolatileString(GetText(text), color);
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


		SDL_Surface* textSurface = createSurface(width, SZ_SCREENHEIGHT, SDL_BLENDMODE_NONE);

		if ((backColor & 0xff) != 0)
		{
			SDL_Color bc = { (unsigned char)(backColor >> 24),
							  (unsigned char)(backColor >> 16),
							  (unsigned char)(backColor >> 8),
							  (unsigned char)(backColor) };
			SDL_FillRect(textSurface, NULL, SDL_MapRGBA(textSurface->format, bc.r, bc.g, bc.b, bc.a));

		}

		SDL_Rect cur = { padding,padding,width,0 };
		SDL_Surface* s;
		int height = 2 * padding;
		int seen_width = 0;
		int cur_width = 0;
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
				if (!word.empty())
				{
					s = TTF_RenderText_Solid(FONT, word.c_str(), c);
					cur.h = s->h;
					cur.w = s->w;
					cur_width += cur.w;

					if (cur.x + cur.w + padding > width)
					{
						/*Line feed*/
						cur.x = padding;
						cur.y += cur.h;
						height += cur.h;
						seen_width = max(seen_width, cur_width);
						cur_width = 0;
					}
					SDL_BlitSurface(s, NULL, textSurface, &cur);
					SDL_FreeSurface(s);
					cur.x += cur.w;
					word = "";
				}

				if (text[i] == '\r' || text[i] == '\n')
				{
					/*Line feed*/
					cur.x = padding;
					cur.y += cur.h;
					height += cur.h;
					seen_width = max(seen_width, cur_width);
					cur_width = 0;
				}
				break;
			default:
				word += text[i];
				break;
			}
		}
		seen_width = max(seen_width, cur_width) + 2 * padding;
		height += cur.h;
		cur.x = cur.y = 0;
		cur.h = height;
		cur.w = width;
		/*Crop*/
		SDL_Surface* croppedTextSurface = createSurface(min(width, seen_width), height);

		SDL_BlitSurface(textSurface, &cur, croppedTextSurface, &cur);
		SDL_Texture* t = this->fromSurface(croppedTextSurface);
		SDL_FreeSurface(croppedTextSurface);
		SDL_FreeSurface(textSurface);
		textures[id] = new Texture(t, min(width, seen_width), height);
	}

	return textures[id];
}

Texture* RenderContext::LoadStringWithIcon(string text, string textureId, int color, int padding, int backColor)
{
	string id = "texticon." + textureId + to_string(color) + "/" + text;
	if (textures.find(id) == textures.end())
	{
		SDL_Surface* icon = Texture::internalLoadBitmapSurface(textureId, false);
		SDL_Rect r;
		SDL_GetClipRect(icon, &r); //Size of the image


		SDL_Color c = { (unsigned char)(color >> 24),
							(unsigned char)(color >> 16),
							(unsigned char)(color >> 8),
							(unsigned char)(color) };

		unsigned char ba = (unsigned char)(backColor);

		//Querying the size of the text
		int w, h;
		if (TTF_SizeText(FONT, text.c_str(), &w, &h))
		{
			cout << TTF_GetError() << endl;
			return NULL;
		}
		int totalW = w + r.w + padding, totalH = max(h, r.h);
		SDL_Surface* back = createSurface(totalW, totalH);

		if (ba != 0) {
			SDL_Color bc = { (unsigned char)(backColor >> 24),
								(unsigned char)(backColor >> 16),
								(unsigned char)(backColor >> 8),
								(unsigned char)(backColor) };

			SDL_FillRect(back, NULL, SDL_MapRGBA(back->format, bc.r, bc.g, bc.b, bc.a));
		}

		SDL_Surface* sText = TTF_RenderText_Solid(FONT, text.c_str(), c);
		if ((color & 0xff) == 0)//transparent, we have to clear it by ourselves since SDL doesn't understand alpha=0.
			SDL_SetSurfaceAlphaMod(sText, 0);

		r.x = r.y = 0;
		SDL_BlitSurface(icon, NULL, back, &r);
		
		//r is now the dest rect of the text
		r.x = padding + r.w;
		r.w = w;
		r.h = h;
		//r.y = TODO vertical centering?
		SDL_BlitSurface(sText, NULL, back, &r);
		
		textures[id] = new Texture(this->fromSurface(back), totalW, totalH);
		SDL_FreeSurface(back);
		SDL_FreeSurface(icon);
		SDL_FreeSurface(sText);
	}

	return textures[id];
}

Texture* RenderContext::LoadText(string text, int color, int width)
{
	return LoadText(text, color, 0, width);
}

Texture* RenderContext::LoadAnimatedString(string text, list<int> colors, int interval, bool loop)
{
	string id = "atext." + to_string(colors.front()) + to_string(colors.back()) + "/" + text;

	if (textures.find(id) == textures.end())
	{
		list<Texture*> listT;
		for (int c : colors)
		{
			listT.push_back(LoadString(text, c));
		}

		textures[id] = new AnimatedTexture(listT, interval, loop);
		listT.clear();
	}

	return textures[id];
}

Texture* RenderContext::LoadAnimatedBoxedString(string text, list<int> colors, list<int> bgcolors, int interval, bool loop)
{
	string id = "atext." + to_string(colors.front()) + to_string(bgcolors.back()) + "/" + text; //heuristical anti-collision (TODO?enough for now)

	if (textures.find(id) == textures.end())
	{
		list<Texture*> listT;
		auto iter = bgcolors.begin();
		for (int c : colors)
		{
			listT.push_back(LoadVolatileString(text, c, *iter));
			iter++;
		}

		textures[id] = new AnimatedTexture(listT, interval, loop);
		listT.clear();
	}

	return textures[id];
}

TTF_Font* RenderContext::FONT;
int RenderContext::FONTSIZE;
unordered_map<string, Texture*> RenderContext::textures;

Texture* RenderContext::LoadVolatileString(string text, int color, int backColor)
{
	SDL_Color c = { (unsigned char)(color >> 24),
							(unsigned char)(color >> 16),
							(unsigned char)(color >> 8),
							(unsigned char)(color) };

	unsigned char ba = (unsigned char)(backColor);
	SDL_Surface* back = NULL;
	int w, h;
	if (ba != 0) {
		SDL_Color bc = { (unsigned char)(backColor >> 24),
							(unsigned char)(backColor >> 16),
							(unsigned char)(backColor >> 8),
							(unsigned char)(backColor) };
		if (TTF_SizeText(FONT, text.c_str(), &w, &h))
		{
			cout << TTF_GetError() << endl;
			return NULL;
		}
		back = createSurface(w, h);
		SDL_FillRect(back, NULL, SDL_MapRGBA(back->format, bc.r, bc.g, bc.b, bc.a));
	}

	SDL_Surface* s = TTF_RenderText_Solid(FONT, text.c_str(), c);
	if ((color & 0xff) == 0)//transparent, we have to clear it by ourselves since SDL doestn't understand alpha=0.
		SDL_SetSurfaceAlphaMod(s, 0);
	SDL_Texture* t;
	if (ba != 0)
	{
		SDL_BlitSurface(s, NULL, back, NULL);

		t = this->fromSurface(back);
		SDL_FreeSurface(back);
	}
	else
		t = this->fromSurface(s);

	SDL_FreeSurface(s);

	if (ba == 0 && TTF_SizeText(FONT, text.c_str(), &w, &h))
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
		delete entry.second;
	}
	textures.clear();
}