#include "Key.h"

Key::Key(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "key", renderer), id(identifier)
{

}

char Key::getId()
{
	return id;
}
