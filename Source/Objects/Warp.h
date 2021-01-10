#ifndef WARP_H
#define WARP_H

#include "Object.h"
#include <string>
#include <sstream>

using namespace std;

class Map;
class MainMenu;

/// <summary>
/// A Warp is an Object that teleports the Player to a Block, that may be situated in a different Room, Map, or even World.
/// </summary>
class Warp : public Object
{
protected:
	/// <summary>
	/// The Map we are going to warp to. If <see cref="Warp::destMap">destMap</see> is equal to -1, we return to the <see cref="MainMenu">main menu Map</see>.
	/// </summary>
	int destMap;
	
	/// <summary>
	/// The Room we are going to warp to.
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
	/// The delay, in ticks, before the Warp is active (if for example we want the Player to warp back to the <see cref="MainMenu">main menu Map</see> after a certain amount of time).
	/// </summary>
	int delay;
	
	/// <summary>
	/// If not empty, the Warp is to be done toward a different world.
	/// </summary>
	string destWorld;
	
public:
	/// <summary>
	/// Destructor.
	/// </summary>
	~Warp();

	/// <summary>
	/// Constructor.
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
	Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay = 0, string destWorld = "");


	/// <summary>
	/// Constructor used to deduce the members from a string when creating <see cref="Map">Maps</see>.
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="identifier"></param>
	/// <param name="renderer"></param>
	Warp(string information, int posx, int posy,  RenderContext& renderer);
	
	/// <summary>
	/// How does a Warp interact with the Player?
	/// </summary>
	/// <param name="game"></param>
	bool updateObject(GAME* game);

	/// <summary>
	/// We encode a Warp with the <see cref="Warp::id">identifier</see>, the <see cref="Warp::destMap">destination Map</see>, <see cref="Warp::destRoom">destination Room</see>, <see cref="Warp::destX">destination x</see> and <see cref="Warp::destY">destination y</see>, followed by two optional parameters, the first being the <see cref="Warp::delay">delay</see> and the second being the <see cref="Warp::destWorld">destination World</see>.
	/// </summary>
	string objectToString() const;
	
};

#endif
