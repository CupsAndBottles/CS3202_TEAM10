#pragma once

#include "cppunit\extensions\HelperMacros.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\StmtTypeTable.h"

class ParentStmtTypeTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParentStmtTypeTableTest);
	CPPUNIT_TEST(TestParentToChildrenTTable);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	ParentStmtTypeTableTest(void);

	void TestParentToChildrenTTable();

	~ParentStmtTypeTableTest(void);

};

