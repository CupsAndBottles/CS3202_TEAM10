#pragma once

#include "cppunit/extensions/HelperMacros.h"

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(TestProcedureParsing);
	CPPUNIT_TEST(TestAssignmentParsing);
	CPPUNIT_TEST(TestCallParsing);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestProcedureParsing();
	void TestAssignmentParsing();
	void TestCallParsing();
};

