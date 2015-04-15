#pragma once

#define NextBipTest_h

#include <cppunit\extensions\HelperMacros.h>

#include "..\SPA\Program\Program.h"	
#include "..\SPA\Parser\Parser.h"
#include "..\SPA\Parser\ParserTester.h"

class NextBipTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(NextBipTest);

	CPPUNIT_TEST(TestGetNextAfter);
	/*CPPUNIT_TEST(TestGetNextBefore);
	CPPUNIT_TEST(TestGetReturnTo);
	CPPUNIT_TEST(TestGetEntryPoint);*/
	CPPUNIT_TEST(TestGetNextBipTAfter);
	CPPUNIT_TEST(TestGetNextBipTBefore);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestGetNextAfter();
	void TestGetNextBefore();
	void TestGetNextBipTAfter();
	void TestGetNextBipTBefore();

	NextBipTest(void);
	~NextBipTest(void);

private:
	void ClearAllData();
};

