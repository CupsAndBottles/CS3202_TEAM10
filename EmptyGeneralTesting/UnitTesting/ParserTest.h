#pragma once

#include "cppunit/extensions/HelperMacros.h"

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(TestSimpleAssignmentParsing);
	CPPUNIT_TEST(TestAssignmentParsing);
	CPPUNIT_TEST(TestWhileParsing);
	CPPUNIT_TEST(TestNestedWhileParsing);
	CPPUNIT_TEST(TestParsing);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	ParserTest();

	void TestSimpleAssignmentParsing();
	void TestAssignmentParsing();
	void TestWhileParsing();
	void TestNestedWhileParsing();
	void TestParsing();
};

