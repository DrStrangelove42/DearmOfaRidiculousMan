#ifndef TEST_INTELLIGENT_MONSTER_H
#define TEST_INTELLIGENT_MONSTER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Characters/IntelligentMonster.h"
#include "../../Source/Maps/Room.h"
#include "../Base/MockRenderContext.h"

class IntelligentMonsterTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(IntelligentMonsterTest);
	CPPUNIT_TEST(movementTest);
	CPPUNIT_TEST_SUITE_END();
protected:
	MockRenderContext* r1;
public:
	void movementTest();
	void setUp();
	void tearDown(); 
};

#endif
