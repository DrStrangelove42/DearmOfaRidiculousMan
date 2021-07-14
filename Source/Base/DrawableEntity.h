#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include "Entity.h"
#include "../Base/utils.h"
#include "Texture.h"

/// <summary>
/// A DrawableEntity is an Entity that can be drawn in the Window.
/// </summary>
class DrawableEntity : Entity
{
protected:
	/// <summary>
	/// x coordinate.
	/// </summary>
	int x;

	/// <summary>
	/// y coordinate.
	/// </summary>
	int y;

	/// <summary>
	/// The Texture ID
	/// </summary>
	string texture;
	
	/// <summary>
	/// The loaded <see cref="Texture">Texture</see>.
	/// </summary>
	Texture* loadedTx;
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	DrawableEntity(int x, int y, RenderContext& renderer, string tx);
	
	/// <summary>
	/// Constructor from a pre-existing Texture.
	/// </summary>
	DrawableEntity(int x, int y, Texture* tx);
	
	/// <summary>
	/// Forces the object to reload the <see cref="Texture">Texture</see> corresponding to the current ID in 'texture'.
	/// Note that there is no function to change the <see cref="Texture">Texture</see> from outside of the object, because we
	/// don't want to, for now.
	/// </summary>
	/// <param name="renderer"></param>
	virtual void updateTexture(RenderContext& renderer);

	/// <summary>
	/// Set the Texture.
	/// </summary>
	/// <param name="texture"></param>
	void setTexture(Texture* texture);

	/// <summary>
	/// Returns the current texture.
	/// </summary>
	/// <returns></returns>
	Texture* getTexture() const;

	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">blocks</see>) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">X Offset, in blocks.</param>
	/// <param name="offsetY">Y Offset, in blocks.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;

	/// <summary>
	/// Absolute rendering of the DrawableEntity (useful to draw it somewhere else outside of a Map)
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="xx"></param>
	/// <param name="yy"></param>
	void sideRender(RenderContext& renderer, int xx, int yy) const;

	string& getTextureID();
};

#endif // !DRAWABLE_ENTITY_H
