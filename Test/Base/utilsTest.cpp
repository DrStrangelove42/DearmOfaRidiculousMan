#include "utilsTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UtilsTest);

void UtilsTest::TestRandRange(void) 
{
	CPPUNIT_ASSERT(GetRandom(15) < 15);
	CPPUNIT_ASSERT(GetRandom(22) >= 0);
}

void UtilsTest::Textures(void) 
{
	//CPPUNIT_ASSERT(RenderContext::textures.empty());
}

void UtilsTest::setUp()
{
	CPPUNIT_ASSERT(InitUtils() == 0);
}

void UtilsTest::tearDown()
{
	//FreeTextures();
}
