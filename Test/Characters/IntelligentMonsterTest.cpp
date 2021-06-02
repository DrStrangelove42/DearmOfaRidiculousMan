#include "IntelligentMonsterTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(IntelligentMonsterTest);

void IntelligentMonsterTest::movementTest()
{
	Player p(*r1, "", 0, 15, 10, 40);
	Room room1(5, 5, 0, 0, p, *r1);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Block* b = new FloorBlock(i, j, *r1);
			room1.replaceBlock(b);
		}
	}

	IntelligentMonster monster(*r1, p, &room1, "empty", 1, 0, 0, 0, 0, 0, 0, true, true);
	monster.teleport(0, 0);
	p.teleport(4, 4);

	for (int i = 0; i < 5; i++)
	{
		CPPUNIT_ASSERT(monster.getX() == i && monster.getY() == i);
		monster.tick(0, NULL);
	}
}

void IntelligentMonsterTest::setUp()
{
	r1 = new MockRenderContext();
}

void IntelligentMonsterTest::tearDown()
{
	delete r1;
}
