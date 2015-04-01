#include <cppunit\config\SourcePrefix.h>

#include "FollowsStmtTypeTableTest.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\StmtTypeTable.h"

#include <algorithm>

void FollowsStmtTypeTableTest::setUp() {
	Follows::ClearData();
	StmtTypeTable::ClearData();

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

}

void FollowsStmtTypeTableTest::tearDown() {
	Follows::ClearData();
	StmtTypeTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(FollowsStmtTypeTableTest);

void FollowsStmtTypeTableTest::TestBeforeToAfterTBV() {
	Follows::CreateBeforeToAfterTBV();

	CPPUNIT_ASSERT(Follows::IsFollowsTBV(1, 2));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(1, 4));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(1, 3));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(2, 7));
	CPPUNIT_ASSERT(Follows::IsFollowsTBV(6, 10));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(0, 1));
	CPPUNIT_ASSERT(!Follows::IsFollowsTBV(1, 11));
}

void FollowsStmtTypeTableTest::TestBeforeToAfterTTable() {
	Follows::CreateBeforeToAfterTTable();

	vector<int> followsAfterT1 = Follows::GetStoredFollowsTAfter(1);
	CPPUNIT_ASSERT_EQUAL(3, (int) followsAfterT1.size());

	sort(followsAfterT1.begin(), followsAfterT1.end());
	CPPUNIT_ASSERT_EQUAL(2, followsAfterT1.at(0));
	CPPUNIT_ASSERT_EQUAL(4, followsAfterT1.at(1));
	CPPUNIT_ASSERT_EQUAL(7, followsAfterT1.at(2));
	
	vector<int> followsAfterT3 = Follows::GetStoredFollowsTAfter(3);
	CPPUNIT_ASSERT_EQUAL(0, (int) followsAfterT3.size());

	vector<int> followsAfterT6 = Follows::GetStoredFollowsTAfter(6);
	CPPUNIT_ASSERT_EQUAL(1, (int) followsAfterT6.size());
	CPPUNIT_ASSERT_EQUAL(10, followsAfterT6.at(0));

}

void FollowsStmtTypeTableTest::TestAfterToBeforeTTable() {
	Follows::CreateAfterToBeforeTTable();

	vector<int> followsBeforeT10 = Follows::GetStoredFollowsTBefore(10);
	CPPUNIT_ASSERT_EQUAL(1, (int) followsBeforeT10.size());
	CPPUNIT_ASSERT_EQUAL(6, followsBeforeT10.at(0));

	vector<int> followsBeforeT7 = Follows::GetStoredFollowsTBefore(7);
	CPPUNIT_ASSERT_EQUAL(3, (int) followsBeforeT7.size());

	sort(followsBeforeT7.begin(), followsBeforeT7.end());
	CPPUNIT_ASSERT_EQUAL(1, followsBeforeT7.at(0));
	CPPUNIT_ASSERT_EQUAL(2, followsBeforeT7.at(1));
	CPPUNIT_ASSERT_EQUAL(4, followsBeforeT7.at(2));

	vector<int> followsBeforeT3 = Follows::GetStoredFollowsTBefore(3);
	CPPUNIT_ASSERT_EQUAL(0, (int) followsBeforeT3.size());

	vector<int> followsBeforeT1 = Follows::GetStoredFollowsTBefore(1);
	CPPUNIT_ASSERT_EQUAL(0, (int) followsBeforeT1.size());

	vector<int> followsBeforeT0 = Follows::GetStoredFollowsTBefore(0);
	CPPUNIT_ASSERT_EQUAL(0, (int) followsBeforeT0.size());

}

FollowsStmtTypeTableTest::FollowsStmtTypeTableTest(void) {

}

FollowsStmtTypeTableTest::~FollowsStmtTypeTableTest(void) {
}
