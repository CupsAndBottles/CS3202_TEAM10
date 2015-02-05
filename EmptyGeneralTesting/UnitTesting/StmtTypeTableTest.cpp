#include <cppunit\config\SourcePrefix.h>

#include "..\SPA\PKB\StmtTypeTable.h"
#include "StmtTypeTableTest.h"

#include <iostream>
#include <string>
#include <stdint.h>


void StmtTypeTableTest::setUp() {
	StmtTypeTable::ClearData();
}

void StmtTypeTableTest::tearDown() {
	StmtTypeTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(StmtTypeTableTest);

void StmtTypeTableTest::GetAllStmtsOfTypeTest() {
	StmtTypeTable::ClearData();

	StmtTypeTable::Insert(1, ASSIGN);
	StmtTypeTable::Insert(2, WHILE);
	
	vector<int> resultTest = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
	CPPUNIT_ASSERT_EQUAL(1, resultTest[0]);
}

void StmtTypeTableTest::CheckIfStmtOfTypeTest() {
	StmtTypeTable::ClearData();

	StmtTypeTable::Insert(1, ASSIGN);
	StmtTypeTable::Insert(2, WHILE);

	CPPUNIT_ASSERT(StmtTypeTable::CheckIfStmtOfType(1, ASSIGN)); 
	CPPUNIT_ASSERT(StmtTypeTable::CheckIfStmtOfType(2, WHILE)); 
}

void StmtTypeTableTest::InsertTest() {
	StmtTypeTable::ClearData();
	
	StmtTypeTable::Insert(1, ASSIGN);

	vector <int> resultTestInsert = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
	CPPUNIT_ASSERT(!(resultTestInsert.empty())); 
}