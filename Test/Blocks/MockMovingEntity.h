#include "../../Source/Characters/MovingEntity.h"

class MockMovingEntity : public MovingEntity
{
public:
	MockMovingEntity(int x, int y) : MovingEntity(x, y, NULL) {}
	virtual void tick(int time, GAME* game) {}
};