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

class UltimateWithAndTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(UltimateWithAndTest);
	//CPPUNIT_TEST(WithAndTest1);
	//CPPUNIT_TEST(WithAndTest2);
	//CPPUNIT_TEST(WithAndTest3);
	CPPUNIT_TEST(WithAndTest4);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void WithAndTest1();
	void WithAndTest2();
	void WithAndTest3();
	void WithAndTest4();
};
