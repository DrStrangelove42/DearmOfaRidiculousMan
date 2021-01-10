#ifndef BANNER_H
#define BANNER_H

#include <string>
#include "Menu.h"
#include "../Base/config.h"

using namespace std;

/// <summary>
/// A Banner is a type of Menu that simply displays some text on the screen for a specified amount of time, useful when creating a Story (for example to display a chapter name).
/// </summary>
class Banner : public Menu
{ 
protected:
	/// <summary>
	/// The amount of time the Banner is shown for.
	/// </summary>
	int delay;
	
	/// <summary>
	/// The time at which the Banner is first displayed.
	/// </summary>
	int beginTime;

	/// <summary>
	/// Name of the World to display after the Banner has been been displayed for the correct amount of time (<see cref="Banner::delay">delay</see>).
	/// </summary>
	string worldName;
	
	/// <summary>
	/// <see cref="GAME::currentMapId">Index</see> of the Map in the Worldto display after the Banner has been been displayed for the correct amount of time (<see cref="Banner::delay">delay</see>).
	/// </summary>
	int mapIndex;
	
	/// <summary>
	/// <see cref="Map::currentRoom">Index</see> of the Room in the Map to display after the Banner has been been displayed for the correct amount of time (<see cref="Banner::delay">delay</see>).
	/// </summary>
	int roomIndex;
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	Banner(Player& p, GAME* g, const  string text, const  int delay, const string worldName, const  int mapIndex, const  int roomIndex);

	/// <summary>
	/// Sets <see cref="Banner::beginTime">beginTime</see> to the current time.
	/// </summary>
	void reset();

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~Banner();
	
	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
 
	/// <summary>
	/// Time management.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
 
};

#endif
