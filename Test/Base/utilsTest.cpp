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

void UtilsTest::TestEatTokenEx(void)
{
	string toParse = "  Paris, New York ,   Santiago ->>";
	string t1 = EatTokenEx(toParse, ',');
	CPPUNIT_ASSERT(toParse == " New York ,   Santiago ->>");
	CPPUNIT_ASSERT(t1 == "Paris");
	t1 = EatTokenEx(toParse);
	CPPUNIT_ASSERT(toParse == "York ,   Santiago ->>");
	CPPUNIT_ASSERT(t1 == "New");
	t1 = EatTokenEx(toParse, ',');
	CPPUNIT_ASSERT(toParse == "   Santiago ->>");
	CPPUNIT_ASSERT(t1 == "York");
}

void UtilsTest::setUp()
{
	//CPPUNIT_ASSERT(InitUtils() == 0);
}

void UtilsTest::tearDown()
{
	//FreeTextures();
}
