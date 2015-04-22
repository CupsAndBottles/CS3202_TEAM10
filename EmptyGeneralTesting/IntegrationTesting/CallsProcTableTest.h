#pragma once

#include "cppunit\extensions\HelperMacros.h"
#include "..\SPA\PKB\calls.h"
#include "..\SPA\PKB\ProcTable.h"

class CallsProcTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(CallsProcTableTest);
	CPPUNIT_TEST(TestCallingToCalledTBV);
	CPPUNIT_TEST(TestCallingToCalledTTable);
	CPPUNIT_TEST(TestCalledToCallingTTable);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	CallsProcTableTest(void);

	void TestCallingToCalledTBV();
	void TestCallingToCalledTTable();
	void TestCalledToCallingTTable();

	~CallsProcTableTest(void);
};

