#include "PlayerTest.h"
#include "../Base/MockWindow.h"
#include "../Base/MockRenderContext.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PlayerTest);

MockRenderContext* r;

void PlayerTest::damageTest()
{
	Player p(*r, 0, 15, 10, 40);

	p.damage(20);
	CPPUNIT_ASSERT(p.getHealth() == 30);
	p.damage(10);
	CPPUNIT_ASSERT(p.getHealth() == 30);
	p.damage(40);
	CPPUNIT_ASSERT(!p.isAlive());
}

void PlayerTest::killTest()
{
	Player p(*r, 1, 15, 10, 40);
	p.kill();
	p.kill();
	CPPUNIT_ASSERT(!p.isAlive());
}

void PlayerTest::setUp()
{
	Window* m = new MockWindow();
	r = new MockRenderContext(*m);
}

void PlayerTest::tearDown()
{
	
}
