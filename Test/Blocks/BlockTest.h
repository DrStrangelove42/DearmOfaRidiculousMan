#ifndef TEST_PLAYER_H
#define TEST_PLAYER_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Blocks/Block.h"
#include "../Base/MockRenderContext.h"
#include "MockMovingEntity.h"

class BlockTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(BlockTest);
	CPPUNIT_TEST(teleportTest);
	 
	CPPUNIT_TEST_SUITE_END();
protected:
	MockRenderContext* r;
	Window* m;
public:
	void teleportTest();
	 
	void setUp();
	void tearDown(); 
};

#endif