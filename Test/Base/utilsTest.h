#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Base/utils.h"

class UtilsTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UtilsTest);
	CPPUNIT_TEST(TestRandRange);
	CPPUNIT_TEST(Textures);
	CPPUNIT_TEST(TestEatTokenEx);
	CPPUNIT_TEST_SUITE_END();

public:
	void TestRandRange(void);
	void Textures(void);
	void TestEatTokenEx(void);
	virtual void setUp();
	virtual void tearDown(); 
};

#endif