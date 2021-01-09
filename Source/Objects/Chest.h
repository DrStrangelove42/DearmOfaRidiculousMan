#ifndef CHEST_H
#define CHEST_H

#include "Object.h"
#include "../Objects/Sword.h"
#include "../Objects/Shield.h"
#include <unordered_map>

class Chest : public Object
{
private:
	/// <summary>
	/// An array of items contained in the chest. 
	/// </summary>
	unordered_map<Object, int, ObjectHash> contents;
public:
	/*Destructor*/
	~Chest();

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Chest(string identifier, int posx, int posy, RenderContext& renderer);
	
	/// <summary>
	/// Constructor used to deduce the members from a string when creating maps
	/// </summary>
	/// <param name="headerline"></param>
	/// <param name="uniqueId"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	Chest(string headerline, int* uniqueId, int posx, int posy, RenderContext& renderer);
	
	/// <summary>
	/// Returns a reference to the array of objects that are in the chest.
	/// </summary>
	/// <returns></returns>
	unordered_map<Object, int, ObjectHash>& getContents();

	/// <summary>
	/// Adds count times the object obj to the chest.
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="count"></param>
	void addObject(Object obj, int count = 1);

	/// <summary>
	/// How does a chest interact with the player?
	/// </summary>
	/// <param name="game"></param>
	bool updateObject(GAME* game);

	/// <summary>
	/// We encode a chest with its id followed by the encoding of each of the objects in its contents, in parentheses.
	/// </summary>
	string objectToString() const;
};

#endif
