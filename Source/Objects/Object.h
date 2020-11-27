#ifndef OBJECT_H
#define OBJECT_H

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/game.h"
#include "../Characters/Player.h"

class Object : public Entity
{
protected:
	/// <summary>
	/// Identifier of the object
	/// </summary>
	string id;

	/// <summary>
	/// Position of the object
	/// </summary>
	int x;

	/// <summary>
	/// Position of the object
	/// </summary>
	int y;

	/// <summary>
	/// Player
	/// </summary>
	Player& player;


	/// <summary>
	/// The texture ID
	/// </summary>
	string texture;

	/// <summary>
	/// The loaded texture
	/// </summary>
	Texture* loadedTx;

public:
	~Object();

	/// <summary>
	/// Initialises a new Object with the specified informations.
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="player"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	Object(string identifier, int posx, int posy, Player& player, string tx, RenderContext& renderer, bool trav);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="other"></param>
	Object(const Object& other);

	/// <summary>
	/// 
	/// </summary>
	bool traversable;

	/* Getters */
	int getX();
	int getY();
	string getId() const;
	bool getTrav();

	/// <summary>
	/// Change the object position. 
	/// </summary>
	/// <param name="px"></param>
	/// <param name="py"></param>
	void move(int px, int py);

	/// <summary>
	///  Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="ea"></param>
	virtual void updateObject(Player& p, RenderContext& renderer, GAME* game);

	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="renderer"></param>
	virtual void tick(int time, RenderContext& renderer, GAME* game);

	/// <summary>
	/// Forces the object to reload the texture corresponding to the current ID in <texture>.
	/// Note that there is no function to change the texture from the outside of the object, because we
	///	don't want to, for now.
	/// </summary>
	/// <param name="renderer"></param>
	virtual void updateTexture(RenderContext& renderer);

	bool operator== (const Object& otherObj) const
	{
		return otherObj.id == id;
	}
};

/// <summary>
/// Map helpers
/// </summary>
struct ObjectHash
{
	size_t operator()(const Object& o) const
	{
		return hash<string>()(o.getId());
	}
};

#endif
