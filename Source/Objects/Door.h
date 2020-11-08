#ifndef DOOR_H
#define DOOR_H

#include "Object.h"

class Door : public Object
{
 private:
  /*Each door has a unique character as an identifier, and the door can be unlocked by a key iff they have the same identifier. */
  char id;
 public:
  /*Constructor*/
  Door(char identifier, int posx, int posy, Player& p, RenderContext& renderer);
  char GetId();
};

#endif
