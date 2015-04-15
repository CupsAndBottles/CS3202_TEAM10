#include <cppunit\config\SourcePrefix.h>

#include <iostream>
#include <algorithm>

#include "NextBipTest.h"
#include "..\SPA\PKB\NextBip.h"

#include "..\SPA\PKB\Next.h"
#include "..\SPA\PKB\Calls.h"
#include "..\SPA\PKB\ProcTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\Parser\Parser.h"
#include "..\SPA\Parser\ParserTester.h"

void NextBipTest::setUp() {
	ClearAllData();
}

void NextBipTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(NextBipTest);

void NextBipTest::ClearAllData() {
	Program::ClearAll();
	StmtTypeTable::ClearData();
	ProcTable::ClearData();
	Calls::ClearData();
	Next::ClearData();
	NextBip::ClearData();
}

NextBipTest::NextBipTest(void) {
}

void NextBipTest::TestGetNextAfter() {
	ParserTester tester("ParserTestFiles/");
	tester.ParseSource("NextBipCallOnceTest.txt");

	// procedure test1
	CPPUNIT_ASSERT_EQUAL(2, NextBip::GetNextAfter(1).at(0));
	CPPUNIT_ASSERT_EQUAL(14, NextBip::GetNextAfter(2).at(0));
	//CPPUNIT_ASSERT_EQUAL(3, NextBip::GetNextAfter(17).at(0));	// should be -1? since we don't know the state
	CPPUNIT_ASSERT_EQUAL(4, NextBip::GetNextAfter(3).at(0));
	CPPUNIT_ASSERT_EQUAL(18, NextBip::GetNextAfter(4).at(0));
	//CPPUNIT_ASSERT_EQUAL(5, NextBip::GetNextAfter(20).at(0));	// should be -1? since we don't know the state

	// procedure test2
	// procedure multPaths

}

void NextBipTest::TestGetNextBipTAfter() {
	ParserTester tester("ParserTestFiles/");
	tester.ParseSource("NextBipCallOnceTest.txt");

	// procedure test1
	vector<int> nextBipTAfter1 = NextBip::GetNextBipTAfter(1);
	CPPUNIT_ASSERT_EQUAL(11, (int) nextBipTAfter1.size());
	sort(nextBipTAfter1.begin(), nextBipTAfter1.end());

	CPPUNIT_ASSERT_EQUAL(2, nextBipTAfter1.at(0));
	CPPUNIT_ASSERT_EQUAL(3, nextBipTAfter1.at(1));
	CPPUNIT_ASSERT_EQUAL(5, nextBipTAfter1.at(3));
	CPPUNIT_ASSERT_EQUAL(14, nextBipTAfter1.at(4));
	CPPUNIT_ASSERT_EQUAL(17, nextBipTAfter1.at(7));
	CPPUNIT_ASSERT_EQUAL(18, nextBipTAfter1.at(8));
	CPPUNIT_ASSERT_EQUAL(20, nextBipTAfter1.at(10));

	// procedure two
	vector<int> nextBipTAfter19 = NextBip::GetNextBipTAfter(19);
	CPPUNIT_ASSERT_EQUAL(1, (int) nextBipTAfter19.size());
	
	CPPUNIT_ASSERT_EQUAL(20, nextBipTAfter19.at(0));

	// procedure test2
	vector<int> nextBipTAfter6 = NextBip::GetNextBipTAfter(6);
	CPPUNIT_ASSERT_EQUAL(14, (int) nextBipTAfter6.size());
	sort(nextBipTAfter6.begin(), nextBipTAfter6.end());
	
	CPPUNIT_ASSERT_EQUAL(1, nextBipTAfter6.at(0));
	CPPUNIT_ASSERT_EQUAL(5, nextBipTAfter6.at(4));
	CPPUNIT_ASSERT_EQUAL(7, nextBipTAfter6.at(5));
	CPPUNIT_ASSERT_EQUAL(8, nextBipTAfter6.at(6));
	CPPUNIT_ASSERT_EQUAL(14, nextBipTAfter6.at(7));
	CPPUNIT_ASSERT_EQUAL(17, nextBipTAfter6.at(10));
	CPPUNIT_ASSERT_EQUAL(18, nextBipTAfter6.at(11));
	CPPUNIT_ASSERT_EQUAL(20, nextBipTAfter6.at(13));

	// procedure multpaths
	vector<int> nextBipTAfter12 = NextBip::GetNextBipTAfter(12);
	CPPUNIT_ASSERT_EQUAL(5, (int) nextBipTAfter12.size());
	sort(nextBipTAfter12.begin(), nextBipTAfter12.end());
	
	CPPUNIT_ASSERT_EQUAL(13, nextBipTAfter12.at(0));
	CPPUNIT_ASSERT_EQUAL(24, nextBipTAfter12.at(1));
	CPPUNIT_ASSERT_EQUAL(27, nextBipTAfter12.at(4));

	vector<int> nextBipTAfter10 = NextBip::GetNextBipTAfter(10);
	CPPUNIT_ASSERT_EQUAL(10, (int) nextBipTAfter10.size());
	sort(nextBipTAfter10.begin(), nextBipTAfter10.end());
	
	CPPUNIT_ASSERT_EQUAL(11, nextBipTAfter10.at(0));
	CPPUNIT_ASSERT_EQUAL(13, nextBipTAfter10.at(2));
	CPPUNIT_ASSERT_EQUAL(21, nextBipTAfter10.at(3));
	CPPUNIT_ASSERT_EQUAL(23, nextBipTAfter10.at(5));
	CPPUNIT_ASSERT_EQUAL(24, nextBipTAfter10.at(6));
	CPPUNIT_ASSERT_EQUAL(27, nextBipTAfter10.at(9));
	
}

void NextBipTest::TestGetNextBipTBefore() {
	ParserTester tester("ParserTestFiles/");
	tester.ParseSource("NextBipCallOnceTest.txt");

	// procedure test1
	vector<int> nextBipTBefore4 = NextBip::GetNextBipTBefore(4);
	CPPUNIT_ASSERT_EQUAL(9, (int) nextBipTBefore4.size());
	sort(nextBipTBefore4.begin(), nextBipTBefore4.end());

	CPPUNIT_ASSERT_EQUAL(1, nextBipTBefore4.at(0));
	CPPUNIT_ASSERT_EQUAL(3, nextBipTBefore4.at(2));
	CPPUNIT_ASSERT_EQUAL(6, nextBipTBefore4.at(3));
	CPPUNIT_ASSERT_EQUAL(7, nextBipTBefore4.at(4));
	CPPUNIT_ASSERT_EQUAL(14, nextBipTBefore4.at(5));
	CPPUNIT_ASSERT_EQUAL(17, nextBipTBefore4.at(8));

	// procedure test2
	vector<int> nextBipTBefore7 = NextBip::GetNextBipTBefore(7);
	CPPUNIT_ASSERT_EQUAL(1, (int) nextBipTBefore7.size());
	CPPUNIT_ASSERT_EQUAL(6, nextBipTBefore7.at(0));

	// procedure multpaths
	vector<int> nextBipTBefore11 = NextBip::GetNextBipTBefore(11);
	CPPUNIT_ASSERT_EQUAL(5, (int) nextBipTBefore11.size());
	sort(nextBipTBefore11.begin(), nextBipTBefore11.end());

	CPPUNIT_ASSERT_EQUAL(9, nextBipTBefore11.at(0));
	CPPUNIT_ASSERT_EQUAL(10, nextBipTBefore11.at(1));
	CPPUNIT_ASSERT_EQUAL(21, nextBipTBefore11.at(2));
	CPPUNIT_ASSERT_EQUAL(23, nextBipTBefore11.at(4));

	vector<int> nextBipTBefore13 = NextBip::GetNextBipTBefore(13);
	CPPUNIT_ASSERT_EQUAL(11, (int) nextBipTBefore13.size());
	sort(nextBipTBefore13.begin(), nextBipTBefore13.end());

	CPPUNIT_ASSERT_EQUAL(9, nextBipTBefore13.at(0));
	CPPUNIT_ASSERT_EQUAL(12, nextBipTBefore13.at(3));
	CPPUNIT_ASSERT_EQUAL(21, nextBipTBefore13.at(4));
	CPPUNIT_ASSERT_EQUAL(23, nextBipTBefore13.at(6));
	CPPUNIT_ASSERT_EQUAL(24, nextBipTBefore13.at(7));
	CPPUNIT_ASSERT_EQUAL(27, nextBipTBefore13.at(10));

	// calling from within a container stmt
	vector<int> nextBipTBefore23 = NextBip::GetNextBipTBefore(23);
	CPPUNIT_ASSERT_EQUAL(5, (int) nextBipTBefore23.size());
	sort(nextBipTBefore23.begin(), nextBipTBefore23.end());

	CPPUNIT_ASSERT_EQUAL(9, nextBipTBefore23.at(0));
	CPPUNIT_ASSERT_EQUAL(10, nextBipTBefore23.at(1));
	CPPUNIT_ASSERT_EQUAL(21, nextBipTBefore23.at(2));
	CPPUNIT_ASSERT_EQUAL(23, nextBipTBefore23.at(4));

	vector<int> nextBipTBefore27 = NextBip::GetNextBipTBefore(27);
	CPPUNIT_ASSERT_EQUAL(9, (int) nextBipTBefore27.size());
	sort(nextBipTBefore27.begin(), nextBipTBefore27.end());

	CPPUNIT_ASSERT_EQUAL(9, nextBipTBefore27.at(0));
	CPPUNIT_ASSERT_EQUAL(12, nextBipTBefore27.at(3));
	CPPUNIT_ASSERT_EQUAL(21, nextBipTBefore27.at(4));
	CPPUNIT_ASSERT_EQUAL(23, nextBipTBefore27.at(6));
	CPPUNIT_ASSERT_EQUAL(24, nextBipTBefore27.at(7));
	CPPUNIT_ASSERT_EQUAL(25, nextBipTBefore27.at(8));
}

NextBipTest::~NextBipTest(void) {
}

/*
	check for start of proc
		if start, return to call stmts (prev of return points)
	else check if previous is call
		if prev is call, return ends of procs called
		return all normal
	*/