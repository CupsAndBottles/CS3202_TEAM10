#pragma once

#define AffectsTest_h

#include <cppunit\extensions\HelperMacros.h>
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\Next.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Follows.h"			// only used for if-else
//#include "..\SPA\PKB\ProcTable.h"		// only used for calls
//#include "..\SPA\Program\Program.h"		// only used for calls
//#include "..\SPA\Parser\Parser.h"
//#include "..\SPA\Parser\ParserTester.h"
#include "..\SPA\PKB\Affects.h"

class AffectsTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(AffectsTest);

	CPPUNIT_TEST(TestIsAffects);
	CPPUNIT_TEST(TestGetStmtsAffectedBy);
	CPPUNIT_TEST(TestGetStmtsAffecting);
	//CPPUNIT_TEST(TestIsAffectsCalls);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestIsAffects();
	void TestGetStmtsAffectedBy();
	void TestGetStmtsAffecting();

	//void TestIsAffectsCalls();

private:
	void ClearAllData();

	// misc methods to create stubs from pre-determined code
	void MimicCodeWithAssignOnly();
	void MimicCodeWithAssignWhile();
	void MimicCodeWithAssignIf();
};

