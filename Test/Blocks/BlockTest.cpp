#include "BlockTest.h"
#include "../Base/MockWindow.h"
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
	m = new MockWindow();
	r = new MockRenderContext(*m);
}

void BlockTest::tearDown()
{
	//delete r;
	//delete m; do NOT delete because the destructors of window and rendercontext will be called
	// This is a design flaw, il could be fixed by introducing RenderContext as a base virtual class,
	//and deriving both in parallel MockRenderContext and SDLRenderContext from it.
}
