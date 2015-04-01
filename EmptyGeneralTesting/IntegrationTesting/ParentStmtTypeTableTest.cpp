#include <cppunit\config\SourcePrefix.h>

#include "ParentStmtTypeTableTest.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\StmtTypeTable.h"

#include <iostream>
#include <algorithm>

void ParentStmtTypeTableTest::setUp() {
	Parent::ClearData();
	StmtTypeTable::ClearData();

	Parent::SetParent(1, 2);
	Parent::SetParent(1, 3);
	Parent::SetParent(1, 4);

	Parent::SetParent(2, 21);
	Parent::SetParent(2, 22);

	Parent::SetParent(22, 221);

	StmtTypeTable::Insert(1, WHILE);
	StmtTypeTable::Insert(2, IF);
	StmtTypeTable::Insert(3, ASSIGN);
	StmtTypeTable::Insert(4, ASSIGN);
	StmtTypeTable::Insert(21, ASSIGN);
	StmtTypeTable::Insert(22, WHILE);
	StmtTypeTable::Insert(221, ASSIGN);
}

void ParentStmtTypeTableTest::tearDown() {
	Parent::ClearData();
	StmtTypeTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParentStmtTypeTableTest);

void ParentStmtTypeTableTest::TestParentToChildrenTBV() {
	Parent::CreateParentToChildrenTBV();

	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 2));
	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 21));
	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 221));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(1, 323));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(2, 3));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(0, 4));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(-1, 4));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(22, 222));
}

void ParentStmtTypeTableTest::TestParentToChildrenTTable() {
	Parent::CreateParentToChildrenTTable();

	vector<int> childrenTOf1 = Parent::GetStoredChildrenTOf(1);
	CPPUNIT_ASSERT_EQUAL(6, (int) childrenTOf1.size());
	
	sort(childrenTOf1.begin(), childrenTOf1.end());
	CPPUNIT_ASSERT_EQUAL(2, childrenTOf1.at(0));
	CPPUNIT_ASSERT_EQUAL(3, childrenTOf1.at(1));
	CPPUNIT_ASSERT_EQUAL(4, childrenTOf1.at(2));
	CPPUNIT_ASSERT_EQUAL(21, childrenTOf1.at(3));
	CPPUNIT_ASSERT_EQUAL(22, childrenTOf1.at(4));
	CPPUNIT_ASSERT_EQUAL(221, childrenTOf1.at(5));

	vector<int> childrenTOf0 = Parent::GetStoredChildrenTOf(0);
	CPPUNIT_ASSERT_EQUAL(0, (int) childrenTOf0.size());

}

void ParentStmtTypeTableTest::TestChildrenToParentTTable() {
	Parent::CreateChildrenToParentTTable();

	vector<int> parentTOf1 = Parent::GetStoredParentTOf(1);
	CPPUNIT_ASSERT_EQUAL(0, (int) parentTOf1.size());

	vector<int> parentTOf22 = Parent::GetStoredParentTOf(22);
	CPPUNIT_ASSERT_EQUAL(2, (int) parentTOf22.size());

	sort(parentTOf22.begin(), parentTOf22.end());
	CPPUNIT_ASSERT_EQUAL(1, parentTOf22.at(0));
	CPPUNIT_ASSERT_EQUAL(2, parentTOf22.at(1));
}

ParentStmtTypeTableTest::ParentStmtTypeTableTest(void){
}

ParentStmtTypeTableTest::~ParentStmtTypeTableTest(void){
}
