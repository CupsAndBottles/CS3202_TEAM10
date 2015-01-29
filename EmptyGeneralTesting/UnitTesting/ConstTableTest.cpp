#include <cppunit\config\SourcePrefix.h>

#include "..\SPA\PKB\ConstTable.h"
#include "ConstTableTest.h"

#include <iostream>
#include <string>
#include <stdint.h>

ConstTableTest::ConstTableTest(void) {
}

void ConstTableTest::setUp() {
	ConstTable::ClearData();
}

void ConstTableTest::tearDown() {
	ConstTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(ConstTableTest);

void ConstTableTest::testGetAllConst() {
	CPPUNIT_ASSERT_EQUAL(0, ConstTable::SizeOfConstTable());

	ConstTable::SetStmtUsesConst(1, 1);
	ConstTable::SetStmtUsesConst(1, 2);
	ConstTable::SetStmtUsesConst(2, 1);

	CPPUNIT_ASSERT_EQUAL(3, ConstTable::SizeOfConstTable());
	
	int correctListOfConstants[] = {1, 2};
	vector<int> listOfConstants = ConstTable::GetAllConst();
	CPPUNIT_ASSERT_EQUAL(correctListOfConstants[0], listOfConstants[0]);
	CPPUNIT_ASSERT_EQUAL(correctListOfConstants[1], listOfConstants[1]);

}

ConstTableTest::~ConstTableTest(void) {


}
