#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include "Entity.h"
#include "../Base/utils.h"

class DrawableEntity : Entity
{
protected:
	/* Position coordinates */
	int x;
	int y;

	/// <summary>
	/// The texture ID
	/// </summary>
	string texture;
	/// <summary>
	/// The loaded texture
	/// </summary>
	Texture* loadedTx;

public:
	DrawableEntity(int x, int y, RenderContext& renderer, string tx);
	DrawableEntity(int x, int y, Texture* tx);
	/* Forces the object to reload the texture corresponding to the current ID in <texture>.
	Note that there is no function to change the texture from the outside of the object, because we
	don't want to, for now.*/
	virtual void updateTexture(RenderContext& renderer);

	void setTexture(Texture* texture);

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	string& getTextureID();
};

#endif // !DRAWABLE_ENTITY_H
