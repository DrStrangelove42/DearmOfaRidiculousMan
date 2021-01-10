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
	/// 
	/// </summary>
	string worldName;
	int mapIndex;
	int roomIndex;
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	Banner(Player& p, GAME* g, const  string text, const  int delay, const string worldName, const  int mapIndex, const  int roomIndex);

	void reset();

	virtual ~Banner();
	
	/// <summary>
	/// Event system from the keyboard
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
