#ifndef KEY_H
#define KEY_H

#include "PickableObject.h"

class Key : public PickableObject
{
public: 
	
	/// <summary>
	/// Constructor, the second character of a key's identifier is used to know which doors it can unlock.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Key(string identifier, int posx, int posy, RenderContext& renderer);

	/// <summary>
	/// We encode a key with its id, but only if it is still visible on the map (and therefore usable)
	/// </summary>
	string objectToString() const;
};

#endif
