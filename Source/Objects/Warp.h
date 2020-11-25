#ifndef WARP_H
#define WARP_H

#include "Object.h"
#include <string>

using namespace std;

class Warp : public Object
{
private:
	/// <summary>
	/// 
	/// </summary>
	int destMap;
	/// <summary>
	/// 
	/// </summary>
	int destRoom;
	/// <summary>
	/// 
	/// </summary>
	int destX;
	/// <summary>
	/// 
	/// </summary>
	int destY;
	/// <summary>
	/// 
	/// </summary>
	bool justWarped;
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
	Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, Player& p, RenderContext& renderer);

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
