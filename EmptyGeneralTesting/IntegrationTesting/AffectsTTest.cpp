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

}

void AffectsTTest::TestGetStmtsAffectedTBy() {

}

void AffectsTTest::TestGetStmtsAffectingT() {

}
