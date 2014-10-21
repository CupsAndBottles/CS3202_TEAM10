#pragma once

#define TestParser_h

#include "cppunit/extensions/HelperMacros.h"

class TestParser : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(TestParser);
	CPPUNIT_TEST(TestProcedureParsing);
	CPPUNIT_TEST(TestAssignmentParsing);
	CPPUNIT_TEST(TestCallParsing);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	TestParser();

	void TestProcedureParsing();
	void TestAssignmentParsing();
	void TestCallParsing();
};

