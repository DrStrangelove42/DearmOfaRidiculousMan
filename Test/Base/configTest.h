#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../Source/Base/config.h"

class ConfigTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ConfigTest);
	CPPUNIT_TEST(TestValuesRange);
	CPPUNIT_TEST_SUITE_END();

public:
	 
	void TestValuesRange(void);
};

#endif