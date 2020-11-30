#ifndef KEY_H
#define KEY_H

#include "Object.h"

class Key : public Object
{
public:
	/*Destructor*/
	~Key();
	
	/// <summary>
	/// Constructor, a key's identifier should be the letter k followed by a character c, the key can only unlock doors starting with dc
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Key(string identifier, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// How does a key interact with the player?
	/// </summary>
	/// <param name="game"></param>
	void updateObject(GAME* game);
};

#endif
