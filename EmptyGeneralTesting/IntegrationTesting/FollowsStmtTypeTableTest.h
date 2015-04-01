#pragma once

#include "cppunit\extensions\HelperMacros.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\StmtTypeTable.h"

class FollowsStmtTypeTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(FollowsStmtTypeTableTest);
	CPPUNIT_TEST(TestBeforeToAfterTBV);
	CPPUNIT_TEST(TestBeforeToAfterTTable);
	CPPUNIT_TEST(TestAfterToBeforeTTable);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	FollowsStmtTypeTableTest(void);

	void TestBeforeToAfterTBV();
	void TestBeforeToAfterTTable();
	void TestAfterToBeforeTTable();

	~FollowsStmtTypeTableTest(void);
};

