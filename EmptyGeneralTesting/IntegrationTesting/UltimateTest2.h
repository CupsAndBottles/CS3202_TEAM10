#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "..\SPA\Parser\Parser.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\QueryProcessor\QueryData.h"
#include "..\SPA\QueryProcessor\QueryPreProcessor.h"
#include "..\SPA\QueryProcessor\QueryEvaluator.h"

class UltimateTest2 : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(UltimateTest2);
<<<<<<< HEAD
	/*CPPUNIT_TEST(TestPatternForIf);
	CPPUNIT_TEST(TestCalls);
	CPPUNIT_TEST(TestCallsT);
	CPPUNIT_TEST(TestWith);*/
=======
	//CPPUNIT_TEST(TestPatternForIf);
	//CPPUNIT_TEST(TestCalls);
	//CPPUNIT_TEST(TestCallsT);
	//CPPUNIT_TEST(TestWith);
>>>>>>> origin/dev
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestPatternForIf();
	void TestCalls();
	void TestCallsT();
	void TestWith();
};