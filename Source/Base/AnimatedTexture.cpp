#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(RenderContext& context, string id) : Texture(NULL, 0, 0)
{
	int num = 0;
	SDL_Texture* cur;
	do
	{
		/*The last will determine the texture's size, hopefully they are all the same*/
		cur = internalLoadTexture(context, id + to_string(num), w, h);
		if (cur != NULL)
			frames.push_back(cur);
	} while (cur != NULL);

}

AnimatedTexture::~AnimatedTexture()
{
	for (SDL_Texture* texture : frames)
		SDL_DestroyTexture(texture);
}

void AnimatedTexture::renderUnscaled(RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

void AnimatedTexture::render(RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (NULL != texture)
	{
		SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, width, height };

		context.doRender(texture, NULL, &dst, angle, center, flip);
	}
}