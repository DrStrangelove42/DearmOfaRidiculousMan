#ifndef WARP_H
#define WARP_H

#include "Object.h"
#include <string>

using namespace std;

class Warp : public Object
{
private:
	/// <summary>
	/// The map we are going to warp to. If destMap == -1, we return to the main menu map.
	/// </summary>
	int destMap;
	/// <summary>
	/// The room we are going to warp to.
	/// </summary>
	int destRoom;
	/// <summary>
	/// The x coordinate we are going to warp to.
	/// </summary>
	int destX;
	/// <summary>
	/// The y coordinate we are going to warp to.
	/// </summary>
	int destY;
	/// <summary>
	/// The delay, in ticks, before the warp is active (if for example we want the player to warp back to the main menu map after a certain amount of time).
	/// </summary>
	int delay;
public:
	/*Destructor*/
	~Warp();

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="destMap"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="identifier"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="delay"></param>
	Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, Player& p, RenderContext& renderer, int delay = 0);

	/// <summary>
	/// How does a warp interact with the player?
	/// </summary>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="ea"></param>
	void updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea);
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool getJustWarped();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="b"></param>
	void setJustWarped(bool b);
};

#endif
