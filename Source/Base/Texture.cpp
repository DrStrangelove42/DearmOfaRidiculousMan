#include "Texture.h"

Texture::Texture(RenderContext& context, string id)
{
	SDL_Texture* tx = NULL;
	SDL_Surface* bmp = NULL;

	bmp = SDL_LoadBMP(("Res/" + id + ".bmp").c_str());
	SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xff, 0, 0xff));

	if (NULL == bmp)
		throw runtime_error("Unable to load texture #" + id);

	tx = context.fromSurface(bmp);
	SDL_FreeSurface(bmp);

	if (NULL == tx)
		throw runtime_error("Unable to create texture #" + id);

	texture = tx;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::renderUnscaled(RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != texture)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, w, h };

		/*Later : to clip an image*/
		/*if (clip != NULL) <- <SDL_Rect* clip> an argument of our function
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}*/

		context.doRender(texture, NULL, &dst, angle, center, flip);
	}
}

void Texture::render(RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != texture)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, width, height };

		context.doRender(texture, NULL, &dst, angle, center, flip);
	}
}

int Texture::getWidth() { return w; }
int Texture::getHeight() { return h; }