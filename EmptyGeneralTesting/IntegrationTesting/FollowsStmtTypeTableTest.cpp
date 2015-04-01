#include <cppunit\config\SourcePrefix.h>

#include "FollowsStmtTypeTableTest.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\StmtTypeTable.h"

void FollowsStmtTypeTableTest::setUp() {
	Follows::ClearData();
	StmtTypeTable::ClearData();
}

void FollowsStmtTypeTableTest::tearDown() {
	Follows::ClearData();
	StmtTypeTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(FollowsStmtTypeTableTest);

void FollowsStmtTypeTableTest::TestBeforeToAfterTTable() {
	// set-up
	Follows::SetFollows(1, 2);
	Follows::SetFollows(2, 4);
	Follows::SetFollows(1, 3); // illegal
	Follows::SetFollows(4, 7);
	Follows::SetFollows(6, 10);

	StmtTypeTable::Insert(1, ASSIGN);
	StmtTypeTable::Insert(2, WHILE);
	StmtTypeTable::Insert(4, IF);
	StmtTypeTable::Insert(6, ASSIGN);
	StmtTypeTable::Insert(7, ASSIGN);
	StmtTypeTable::Insert(10, ASSIGN);

	Follows::CreateBeforeToAfterTTable();

	CPPUNIT_ASSERT(Follows::IsFollowsTBV(1, 2));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(1, 4));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(1, 3));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(2, 7));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(6, 10));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(0, 1));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(1, 11));
}

FollowsStmtTypeTableTest::FollowsStmtTypeTableTest(void) {
}


FollowsStmtTypeTableTest::~FollowsStmtTypeTableTest(void) {
}
