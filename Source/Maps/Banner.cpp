#include "Banner.h" 

Banner::Banner(Player& p, GAME* g,const  string text,const  int delay, const string worldName,const  int mapIndex,const  int roomIndex) :
	Menu(p, g), delay(delay), worldName(worldName), mapIndex(mapIndex), roomIndex(roomIndex)
{
	RenderContext* r = g->renderer;
	Texture* t = r->LoadText(text, 0xffffffff, SZ_SCREENWIDTH);
	addLabel(new Label(t, (SZ_SCREENWIDTH - t->getWidth()) / 2, (SZ_SCREENHEIGHT - t->getHeight()) / 2));
	reset();
}

void Banner::reset()
{
	beginTime = GetTime();
}

Banner::~Banner()
{

}

void Banner::onKeyDown(GAME* game)
{

}

void Banner::tick(int time, GAME* game)
{
	if (time - beginTime > delay)
	{
		//warp
		changeMap(game, worldName, mapIndex, roomIndex);
		//tell the story we can go on
		if (player.hasStory())
		{
			player.getStory().continueStory();
		}
	}
}
