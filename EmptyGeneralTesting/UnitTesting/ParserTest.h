#pragma once

#include "cppunit\extensions\HelperMacros.h"
#include "..\SPA\Parser\Parser.h"

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserTest);
	CPPUNIT_TEST(TestSimpleAssignmentParsing);
	CPPUNIT_TEST(TestAdditionParsing);
	CPPUNIT_TEST(TestWhileParsing);
	CPPUNIT_TEST(TestNestedWhileParsing);
	CPPUNIT_TEST(TestParsing);
	CPPUNIT_TEST(TestBracketParsing);
	CPPUNIT_TEST(TestCallParsing);
	CPPUNIT_TEST(TestIfParsing);
	CPPUNIT_TEST(TestOperatorParsing);
	CPPUNIT_TEST(TestProcedureParsing);
	CPPUNIT_TEST_SUITE_END();

public:
	static const string TESTFILE_DIRECTORY;
	void setUp();
	void tearDown();

	ParserTest();

	void TestSimpleAssignmentParsing();
	void TestAdditionParsing();
	void TestWhileParsing();
	void TestNestedWhileParsing();
	void TestParsing();
	void TestBracketParsing();
	void TestCallParsing();
	void TestIfParsing();
	void TestOperatorParsing();
	void TestProcedureParsing();
};

