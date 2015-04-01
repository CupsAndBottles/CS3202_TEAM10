#include <cppunit\config\SourcePrefix.h>

#include "ParentStmtTypeTableTest.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\StmtTypeTable.h"

#include <iostream>

void ParentStmtTypeTableTest::setUp() {
	Parent::ClearData();
	StmtTypeTable::ClearData();
}

void ParentStmtTypeTableTest::tearDown() {
	Parent::ClearData();
	StmtTypeTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParentStmtTypeTableTest);

void ParentStmtTypeTableTest::TestParentToChildrenTTable() {
	// set-up
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

	Parent::CreateParentToChildrenTTable();

	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 2));
	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 21));
	CPPUNIT_ASSERT(Parent::IsParentTBV(1, 221));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(1, 323));
	CPPUNIT_ASSERT(!Parent::IsParentTBV(2, 3));
}

ParentStmtTypeTableTest::ParentStmtTypeTableTest(void){
}

ParentStmtTypeTableTest::~ParentStmtTypeTableTest(void){
}
