#include "Texture.h"

Texture::Texture(RenderContext& context, string id)
{
	SDL_Texture* tx = NULL;
	SDL_Surface* bmp = NULL;

	bmp = SDL_LoadBMP(("Res/" + id + ".bmp").c_str());
	SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xff, 0, 0xff));

	if (NULL == bmp)
		DumpError("Unable to load texture #" + id);

	tx = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);

	if (NULL == tx)
		DumpError("Unable to create texture #" + id);

	texture = tx;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

Texture::render(RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != t)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, w, h };

		/*Later : to clip an image*/
		/*if (clip != NULL) <- <SDL_Rect* clip> an argument of our function
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}*/

		context.doRender(t, NULL, &dst, angle, center, flip);
	}
}