#include "PlayerTest.h"
#include "../Base/MockRenderContext.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PlayerTest);

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

void PlayerTest::experienceTest()
{
	Player p(*r);
	p.gainCoins(500);
	CPPUNIT_ASSERT(p.getMoney() == 500);
	p.gainCoins(-50);
	CPPUNIT_ASSERT(p.getMoney() == 450);
}

void PlayerTest::coinTest()
{
	Player p(*r);
	p.gainExperience(60);
	CPPUNIT_ASSERT(p.getExperience() == 60);
	p.gainExperience(456);
	CPPUNIT_ASSERT(p.getExperience() == 60 + 456);
}

void PlayerTest::inventoryTest()
{
	Player p(*r);
	Object* o = new PickableObject("iden", 0, 0, "Dummy", *r, false);
	CPPUNIT_ASSERT(!p.hasObject("iden"));
	CPPUNIT_ASSERT(!p.hasObject(o));
	p.pickUpObject(static_cast<PickableObject*>(o));
	CPPUNIT_ASSERT(p.hasObject("iden"));
	CPPUNIT_ASSERT(p.hasObject(o));
}

void PlayerTest::setUp()
{ 
	r = new MockRenderContext();
}

void PlayerTest::tearDown()
{
	delete r; 
}
