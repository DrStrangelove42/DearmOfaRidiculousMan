#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(RenderContext& context, string id, int delay) :
	Texture(NULL, 0, 0), delay(delay), curFrame(0), lastTime(0)
{
	int num = 0;
	SDL_Texture* cur = NULL;
	do
	{
		/*The last will determine the texture's size, hopefully they are all the same*/
		cur = internalLoadTexture(context, id + to_string(num++), w, h, true);
		if (cur != NULL)
			frames.push_back(cur);
		
	} while (cur != NULL);

	frameCount = int(frames.size());
}

AnimatedTexture::~AnimatedTexture()
{
	for (SDL_Texture* texture : frames)
		SDL_DestroyTexture(texture);
}

void AnimatedTexture::renderUnscaled(RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	int time = GetTime();
	if (time - lastTime >= delay)
	{
		curFrame = (curFrame + 1) % frameCount;
		lastTime = time;
	}

	internalRenderUnscaled(frames[curFrame], context, x, y, angle, center, flip);
}

void AnimatedTexture::render(RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	int time = GetTime();
	if (time - lastTime >= delay)
	{
		curFrame = (curFrame + 1) % frameCount;
		lastTime = time;
	}

	internalRender(frames[curFrame], context, x, y, width, height, angle, center, flip);
}

void AnimatedTexture::setDelay(int d)
{
	delay = d;
}
