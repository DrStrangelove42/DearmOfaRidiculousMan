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
#include "../Interactions/Story.h"

using namespace std;

/// <summary>
/// The MainMenu is a type of Menu used to greet the user when they start the game.
/// </summary>
class MainMenu : public Menu
{
protected:
	 
	/// <summary>
	/// The current Label of the animation in MainMenu.
	/// </summary>
	Label* animation;
 
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	MainMenu(Player& p, GAME* g);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~MainMenu();
	
	/// <summary>
	/// Called when the user clicks on the Play Button.
	/// </summary>
	/// <param name="id"></param>
	void onPlayClick(int id);

	/// <summary>
	/// Called when the user clicks on the Story Mode Button.
	/// </summary>
	/// <param name="id"></param>
	void onStoryModeClick(int id);

	/// <summary>
	/// Called when the user clicks on the Quit Button.
	/// </summary>
	/// <param name="id"></param>
	void onQuitClick(int id);
	
	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
	
	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">Blocks</see>) into account.
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
