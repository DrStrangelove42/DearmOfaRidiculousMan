#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include "Menu.h"
#include "../Base/game.h"
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
class MainMenu : public Menu
{
protected:
	 
	/// <summary>
	/// 
	/// </summary>
	Label* animation;
	/// <summary>
	/// 
	/// </summary>
	Texture** animationTextures;
 
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	MainMenu(Player& p, GAME* g);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	void onPlayClick(int id);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	void onQuitClick(int id);
	virtual ~MainMenu();
	/// <summary>
	/// Event system from keyboard
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
	/// <summary>
	/// Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;
	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
};

#endif
