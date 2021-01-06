#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Characters/Player.h"

class PlayerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(PlayerTest);
	CPPUNIT_TEST(damageTest	);
	CPPUNIT_TEST_SUITE_END();

public:
	void damageTest();
	void setUp();
	void tearDown(); 
};

#endif