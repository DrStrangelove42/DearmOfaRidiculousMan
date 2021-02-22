#ifndef COIN_H
#define COIN_H

#include "Object.h"
#include "../Base/AnimatedTexture.h"

/// <summary>
/// A Coin is an Object that can be picked up and used to unlock one or several <see cref="Door">Door</see>s.
/// </summary>
class Coin : public Object
{
protected:
	int money;
public: 
	
	/// <summary>
	/// Constructor, id is of the form $X.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="money"></param>
	Coin(string identifier, int posx, int posy, RenderContext& renderer, int money);

	/// <summary>
	/// Constructor from the map parser
	/// </summary>
	/// <param name="headerLine"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Coin(string headerLine, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// Adds the money to the player.
	/// </summary>
	/// <param name="game"></param>
	/// <returns></returns>
	bool updateObject(GAME* game);

	/// <summary>
	/// We encode a coin with its money amount
	/// </summary>
	virtual string objectToString() const;
};

#endif
