#ifndef WARP_H
#define WARP_H

#include "Object.h"
#include <string>
#include <sstream>

using namespace std;

class Map;
class MainMenu;

class Warp : public Object
{
protected:
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
	/// <summary>
	/// If not empty, the warp is to be done toward a different world.
	/// </summary>
	string destWorld;
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
	/// <param name="renderer"></param>
	/// <param name="delay"></param>
	Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay = 0);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="destMap"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="identifier"></param>
	/// <param name="renderer"></param>
	/// <param name="delay"></param>
	/// <param name="destWorld"></param>
	Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay, string destWorld);


	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="identifier"></param>
	/// <param name="renderer"></param>
	Warp(string information, int posx, int posy,  RenderContext& renderer);
	
	/// <summary>
	/// How does a warp interact with the player?
	/// </summary>
	/// <param name="game"></param>
	bool updateObject(GAME* game);

	/// <summary>
	/// We encode a warp with the id, the destination map, room, x and y, followed by two optional parameters, the first being the delay and the second being the destination world.
	/// </summary>
	string objectToString() const;
	
};

#endif
