#ifndef KEY_H
#define KEY_H

#include "PickableObject.h"

class Key : public PickableObject
{
public: 
	
	/// <summary>
	/// Constructor, a key's identifier should be the letter k followed by a character c, the key can only unlock doors starting with dc
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Key(string identifier, int posx, int posy, RenderContext& renderer);
};

#endif
