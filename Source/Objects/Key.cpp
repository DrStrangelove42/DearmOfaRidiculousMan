#include "Key.h"
#include "../Characters/Player.h"

Key::Key(string identifier, int posx, int posy, RenderContext& renderer) :
	PickableObject(identifier, posx, posy, "key", renderer, true)
{

} 