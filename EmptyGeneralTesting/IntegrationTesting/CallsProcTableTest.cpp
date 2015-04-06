#include <cppunit\config\SourcePrefix.h>

#include "CallsProcTableTest.h"
#include "..\SPA\PKB\calls.h"
#include "..\SPA\PKB\ProcTable.h"

#include <algorithm>

void CallsProcTableTest::setUp() {
	Calls::ClearData();
	ProcTable::ClearData();

	Calls::SetCalls(0, 1);
	Calls::SetCalls(1, 2);
	Calls::SetCalls(1, 3);
	Calls::SetCalls(2, 4);
	Calls::SetCalls(3, 5);
	Calls::SetCalls(6, 4);

	ProcTable::InsertProc("Alice");
	ProcTable::InsertProc("Bob");
	ProcTable::InsertProc("Charlie");
	ProcTable::InsertProc("Delta");
	ProcTable::InsertProc("Eve");
	ProcTable::InsertProc("Fire");
	ProcTable::InsertProc("Goat");

}

void CallsProcTableTest::tearDown() {
	Calls::ClearData();
	ProcTable::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(CallsProcTableTest);

void CallsProcTableTest::TestCallingToCalledTBV() {
	Calls::CreateCallingToCalledTBV();

	CPPUNIT_ASSERT(Calls::IsCallsTBV(0, 1));
	CPPUNIT_ASSERT(Calls::IsCallsTBV(0, 5));
	CPPUNIT_ASSERT(Calls::IsCallsTBV(6, 4));
	CPPUNIT_ASSERT(!Calls::IsCallsTBV(-1, 0));
	CPPUNIT_ASSERT(!Calls::IsCallsTBV(6, 0));
	CPPUNIT_ASSERT(!Calls::IsCallsTBV(7, 0));

}

void CallsProcTableTest::TestCallingToCalledTTable() {
	Calls::CreateCallingToCalledTTable();

	vector<int> procsCalledTBy0 = Calls::GetStoredProcsCalledTBy(0);
	CPPUNIT_ASSERT_EQUAL(5, (int) procsCalledTBy0.size());
	sort(procsCalledTBy0.begin(), procsCalledTBy0.end());

	CPPUNIT_ASSERT_EQUAL(1, procsCalledTBy0.at(0));
	CPPUNIT_ASSERT_EQUAL(2, procsCalledTBy0.at(1));
	CPPUNIT_ASSERT_EQUAL(3, procsCalledTBy0.at(2));
	CPPUNIT_ASSERT_EQUAL(4, procsCalledTBy0.at(3));
	CPPUNIT_ASSERT_EQUAL(5, procsCalledTBy0.at(4));

	vector<int> procsCalledTBy2 = Calls::GetStoredProcsCalledTBy(2);
	CPPUNIT_ASSERT_EQUAL(1, (int) procsCalledTBy2.size());
	CPPUNIT_ASSERT_EQUAL(4, procsCalledTBy2.at(0));

	vector<int> procsCalledTBy6 = Calls::GetStoredProcsCalledTBy(6);
	CPPUNIT_ASSERT_EQUAL(1, (int) procsCalledTBy6.size());
	CPPUNIT_ASSERT_EQUAL(4, procsCalledTBy6.at(0));

	vector<int> procsCalledTBy7 = Calls::GetStoredProcsCalledTBy(7);
	CPPUNIT_ASSERT_EQUAL(0, (int) procsCalledTBy7.size());

}

void CallsProcTableTest::TestCalledToCallingTTable() {
	Calls::CreateCalledToCallingTTable();

	vector<int> procsCallingT4 = Calls::GetStoredProcsCallingT(4);
	CPPUNIT_ASSERT_EQUAL(4, (int) procsCallingT4.size());

	sort(procsCallingT4.begin(), procsCallingT4.end());
	CPPUNIT_ASSERT_EQUAL(0, procsCallingT4.at(0));
	CPPUNIT_ASSERT_EQUAL(1, procsCallingT4.at(1));
	CPPUNIT_ASSERT_EQUAL(2, procsCallingT4.at(2));
	CPPUNIT_ASSERT_EQUAL(6, procsCallingT4.at(3));

	vector<int> procsCallingT5 = Calls::GetStoredProcsCallingT(5);
	CPPUNIT_ASSERT_EQUAL(3, (int) procsCallingT5.size());

	sort(procsCallingT5.begin(), procsCallingT5.end());
	CPPUNIT_ASSERT_EQUAL(0, procsCallingT5.at(0));
	CPPUNIT_ASSERT_EQUAL(1, procsCallingT5.at(1));
	CPPUNIT_ASSERT_EQUAL(3, procsCallingT5.at(2));

	vector<int> procsCallingT0 = Calls::GetStoredProcsCallingT(0);
	CPPUNIT_ASSERT_EQUAL(0, (int) procsCallingT0.size());

}

CallsProcTableTest::CallsProcTableTest(void) {
}


CallsProcTableTest::~CallsProcTableTest(void) {
}
