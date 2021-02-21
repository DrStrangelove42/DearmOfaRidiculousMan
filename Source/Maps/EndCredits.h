#ifndef ENDCREDITS_H
#define ENDCREDITS_H

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
/// The EndCredits is a type of Menu used to greet the user when they start the game.
/// </summary>
class EndCredits : public Menu
{
protected:
	 
	/*Two labels whose pointers are saved here to move them in the tick() function.*/

	/// <summary>
	/// The current Label of the animation in EndCredits.
	/// </summary>
	Label* animation;

	/// <summary>
	/// Labels telling devs names.
	/// </summary>
	Label* names;
 
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	EndCredits(Player& p, GAME* g);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~EndCredits();
	
	/// <summary>
	/// Called when the user clicks on the Play Button.
	/// </summary>
	/// <param name="id"></param>
	void onPlayClick(int id);

	
	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
};

#endif
