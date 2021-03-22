#include "BlockTest.h"
#include "../Base/MockRenderContext.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BlockTest);

void BlockTest::teleportTest()
{
	Block* b = new Block(15, 20, "dummy", *r, false);
	MovingEntity *e = new MockMovingEntity(5, 10);
	b->teleportOn(*e);
	CPPUNIT_ASSERT(e->getX() == b->getX());
	CPPUNIT_ASSERT(e->getY() == b->getY());

	delete e;
	delete b;
}

void BlockTest::setUp()
{
	r = new MockRenderContext();
}

void BlockTest::tearDown()
{
	delete r;
}
