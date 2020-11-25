#ifndef MENU_H
#define MENU_H

#include <string>
#include "../Base/events.h"
#include "../Base/Entity.h"
#include "../Base/config.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
#include "../Interactions/Button.h"
#include <iostream>
#include <fstream>
#include "../Objects/Object.h"
#include "../Objects/Chest.h"
#include "../Objects/Door.h"
#include "../Objects/Key.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
 
using namespace std;

/*
A map represents a set of rooms displayed one at a time (or one centered
in the view and the others black or greyed).
The initial room is always the first room in the (non empty) array 'rooms'.
*/
class MainMenu : public Map
{
protected:
	Button** buttons;
	Label** labels;
	Label* animation;
	int buttonCount;
	int labelCount;
	Texture** animationTextures;
	GAME* game;
public:
	MainMenu(Player& p, GAME* g);
	void onPlayClick(int id);
	void onQuitClick(int id);
	virtual ~MainMenu();
	virtual void onMouseEvent(MOUSE_DATA* md);
	/* Event system */
	virtual void onKeyDown(EVENT_ARGS* ea);
	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	/* Time management */
	virtual void tick(int time, RenderContext& r);
};

#endif
