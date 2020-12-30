#ifndef SIGNBOARD_H
#define SIGNBOARD_H

#include "Object.h"
#include "../Base/config.h"
 

class Signboard : public Object
{
protected:
	Texture* textContent;

	void setTexture(string text, RenderContext& renderer);
public:
	/*Destructor*/
	virtual ~Signboard();

	/// <summary>
	/// Initialises a new Signboard with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	/// <param name="attack"></param>
	/// <param name="defense"></param>
	Signboard(string identifier, int posx, int posy, RenderContext& renderer, string content);

	/// <summary>
	/// Initialises a new Signboard from the header line in a map file.
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Signboard(string headerline, int posx, int posy, RenderContext& renderer);


	/// <summary>
	/// Interaction with the game.
	/// </summary>
	/// <param name="game"></param>
	/// <returns>True if the object needs to be removed</returns>
	bool updateObject(GAME* game);
};

#endif
