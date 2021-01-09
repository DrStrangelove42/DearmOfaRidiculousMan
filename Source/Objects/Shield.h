#ifndef SHIELD_H
#define SHIELD_H

#include "PickableObject.h"

using namespace std;

//Identifier starts with sh

class Shield : public PickableObject
{
public:
	/// <summary>
	/// Initialises a new Shield with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	/// <param name="defense"></param>
	Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense = 10);

	/// <summary>
	/// We encode a shield with sh followed by the defense parameter.
	/// </summary>
	string objectToString() const;
};

#endif
