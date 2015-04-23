#include <cppunit\config\SourcePrefix.h>

#include "AffectsTTest.h"
#include "..\SPA\PKB\Affects.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\Parser\Parser.h"
#include "..\SPA\Parser\ParserTester.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKBCleaner.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AffectsTTest);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void AffectsTTest::setUp() {
	Program::ClearAll();
	ParserTester tester(TESTFILE_DIRECTORY);
	tester.ParseSource("AffectsTTest.txt");
}

void AffectsTTest::tearDown() {
	Program::ClearAll();
}

void AffectsTTest::TestIsAffectsT() {
	// test sequential
	CPPUNIT_ASSERT(Affects::IsAffectsT(1, 2));
	CPPUNIT_ASSERT(Affects::IsAffectsT(1, 3));
	CPPUNIT_ASSERT(Affects::IsAffectsT(2, 4));
	CPPUNIT_ASSERT(Affects::IsAffectsT(1, 4));

	// test whileLoop
	CPPUNIT_ASSERT(Affects::IsAffectsT(5, 7));
	CPPUNIT_ASSERT(Affects::IsAffectsT(8, 8));
	CPPUNIT_ASSERT(Affects::IsAffectsT(9, 10));
	CPPUNIT_ASSERT(Affects::IsAffectsT(5, 10));

	// test ifStmt
	CPPUNIT_ASSERT(Affects::IsAffectsT(11, 13));
	CPPUNIT_ASSERT(Affects::IsAffectsT(11, 14));
	CPPUNIT_ASSERT(Affects::IsAffectsT(11, 15));
	CPPUNIT_ASSERT(Affects::IsAffectsT(13, 16));
	CPPUNIT_ASSERT(Affects::IsAffectsT(14, 17));
	CPPUNIT_ASSERT(Affects::IsAffectsT(11, 16));
	CPPUNIT_ASSERT(Affects::IsAffectsT(11, 17));

	// test ifInWhile
	CPPUNIT_ASSERT(Affects::IsAffectsT(19, 21));
	CPPUNIT_ASSERT(Affects::IsAffectsT(19, 22));
	CPPUNIT_ASSERT(Affects::IsAffectsT(22, 23));
	CPPUNIT_ASSERT(Affects::IsAffectsT(23, 24));
	CPPUNIT_ASSERT(Affects::IsAffectsT(22, 22));
	CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT(Affects::IsAffectsT(24, 21)));

	// test whileInIf
	CPPUNIT_ASSERT(Affects::IsAffectsT(26, 29));
	CPPUNIT_ASSERT(Affects::IsAffectsT(29, 31));
	CPPUNIT_ASSERT(Affects::IsAffectsT(26, 31));
}

void AffectsTTest::TestGetStmtsAffectedTBy() {
	vector<int> expectedResult;
	vector<int> actualResult;

	// test sequential
	actualResult = Affects::GetStmtsAffectedTBy(1);
	CPPUNIT_ASSERT_EQUAL(3, (int)actualResult.size());

	expectedResult.push_back(2);
	expectedResult.push_back(3);
	expectedResult.push_back(4);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	// test whileLoop
	actualResult = Affects::GetStmtsAffectedTBy(5);
	CPPUNIT_ASSERT_EQUAL(2, (int)actualResult.size());

	expectedResult.push_back(7);
	expectedResult.push_back(10);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectedTBy(8);
	CPPUNIT_ASSERT_EQUAL(1, (int)actualResult.size());

	expectedResult.push_back(8);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectedTBy(9);
	CPPUNIT_ASSERT_EQUAL(1, (int)actualResult.size());

	expectedResult.push_back(10);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	// test ifStmt
	actualResult = Affects::GetStmtsAffectedTBy(11);
	CPPUNIT_ASSERT_EQUAL(5, (int)actualResult.size());

	expectedResult.push_back(13);
	expectedResult.push_back(14);
	expectedResult.push_back(15);
	expectedResult.push_back(16);
	expectedResult.push_back(17);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectedTBy(14);
	CPPUNIT_ASSERT_EQUAL(1, (int)actualResult.size());

	expectedResult.push_back(17);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectedTBy(15);
	CPPUNIT_ASSERT_EQUAL(0, (int)actualResult.size());

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();
}

void AffectsTTest::TestGetStmtsAffectingT() {
	vector<int> expectedResult;
	vector<int> actualResult;

	// test sequential
	actualResult = Affects::GetStmtsAffectingT(4);
	CPPUNIT_ASSERT_EQUAL(2, (int)actualResult.size());

	expectedResult.push_back(1);
	expectedResult.push_back(2);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	// test whileLoop
	actualResult = Affects::GetStmtsAffectingT(10);
	CPPUNIT_ASSERT_EQUAL(3, (int)actualResult.size());

	expectedResult.push_back(5);
	expectedResult.push_back(7);
	expectedResult.push_back(9);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectingT(8);
	CPPUNIT_ASSERT_EQUAL(1, (int)actualResult.size());

	expectedResult.push_back(8);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	// test ifStmt
	actualResult = Affects::GetStmtsAffectingT(16);
	CPPUNIT_ASSERT_EQUAL(2, (int)actualResult.size());

	expectedResult.push_back(11);
	expectedResult.push_back(13);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectingT(17);
	CPPUNIT_ASSERT_EQUAL(2, (int)actualResult.size());

	expectedResult.push_back(11);
	expectedResult.push_back(14);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectingT(16);
	CPPUNIT_ASSERT_EQUAL(2, (int)actualResult.size());

	expectedResult.push_back(11);
	expectedResult.push_back(13);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();


	actualResult = Affects::GetStmtsAffectingT(15);
	CPPUNIT_ASSERT_EQUAL(1, (int)actualResult.size());

	expectedResult.push_back(11);

	sort(expectedResult.begin(), expectedResult.end());
	sort(actualResult.begin(), actualResult.end());

	CPPUNIT_ASSERT(expectedResult == actualResult);

	expectedResult.clear();
	actualResult.clear();
}
