#include "Texture.h"

Texture::Texture(RenderContext& context, string id)
{
	texture = internalLoadTexture(context, id, w, h);
}

SDL_Texture* Texture::internalLoadTexture(RenderContext& context, string id, int& w, int& h)
{
	SDL_Texture* tx = NULL;
	SDL_Surface* bmp = NULL;

	bmp = SDL_LoadBMP(("Res/" + id + ".bmp").c_str());

	if (NULL == bmp)
	{
		cout << "Unable to load texture #" + id + " : " + string(SDL_GetError()) << endl;
		return NULL;
	}

	SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xff, 0, 0xff));

	tx = context.fromSurface(bmp);
	SDL_FreeSurface(bmp);

	if (NULL == tx)
	{
		cout << "Unable to create texture #" + id + " : " + string(SDL_GetError()) << endl;
		return NULL;
	}

	SDL_QueryTexture(tx, NULL, NULL, &w, &h);

	return tx;
}


Texture::Texture(SDL_Texture* texture, int w, int h) : texture(texture), w(w), h(h)
{

}

Texture::~Texture()
{
	if (NULL != texture)
		SDL_DestroyTexture(texture);
}

void Texture::renderUnscaled(RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	internalRenderUnscaled(texture, context, x, y, angle, center, flip);
}

void Texture::render(RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	internalRender(texture, context, x, y, width, height, angle, center, flip);
}

int Texture::getWidth() { return w; }
int Texture::getHeight() { return h; }


void Texture::internalRender(SDL_Texture* tx, RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != tx)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, width, height };

		context.doRender(tx, NULL, &dst, angle, center, flip);
	}
}

void Texture::internalRenderUnscaled(SDL_Texture* tx, RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != tx)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, w, h };

		/*Later : to clip an image*/
		/*if (clip != NULL) <- <SDL_Rect* clip> an argument of our function
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}*/

		context.doRender(tx, NULL, &dst, angle, center, flip);
	}
}