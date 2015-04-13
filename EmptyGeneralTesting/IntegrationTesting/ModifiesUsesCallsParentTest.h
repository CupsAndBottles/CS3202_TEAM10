#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "..\SPA\Parser\Parser.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Calls.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\QueryProcessor\QueryData.h"
#include "..\SPA\QueryProcessor\QueryPreProcessor.h"
#include "..\SPA\QueryProcessor\QueryEvaluator.h"

class ModifiesUsesCallsParentTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ModifiesUsesCallsParentTest);
	CPPUNIT_TEST(TestCallsUses);
	CPPUNIT_TEST(TestCallsModifies);
	CPPUNIT_TEST(TestParentUses);
	CPPUNIT_TEST(TestParentModifies);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestCallsUses();
	void TestCallsModifies();
	void TestParentUses();
	void TestParentModifies();
};

