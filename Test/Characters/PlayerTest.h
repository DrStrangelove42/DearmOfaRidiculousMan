#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Characters/Player.h"
#include "../Base/MockRenderContext.h"

class PlayerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(PlayerTest);
	CPPUNIT_TEST(damageTest	);
	CPPUNIT_TEST(coinTest);
	CPPUNIT_TEST(experienceTest);
	CPPUNIT_TEST(inventoryTest);
	CPPUNIT_TEST(killTest);
	CPPUNIT_TEST_SUITE_END();
protected:
	MockRenderContext* r;
	Window* m;
public:
	void damageTest();
	void killTest();
	void experienceTest();
	void coinTest();
	void inventoryTest();
	void setUp();
	void tearDown(); 
};

#endif