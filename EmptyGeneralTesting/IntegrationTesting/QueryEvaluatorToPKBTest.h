#pragma once

#include <cppunit\extensions\HelperMacros.h>

#include "Parser\Parser.h"
#include "PKB\VarTable.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\Follows.h"
#include "PKB\Parent.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "Program\Program.h"
#include "QueryProcessor/QueryData.h"
#include "QueryProcessor/QueryValidator.h"
#include "QueryProcessor/QueryEvaluator.h"

class QueryEvaluatorToPKBTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(QueryEvaluatorToPKBTest);
	//CPPUNIT_TEST(TestSelectAll);
	//CPPUNIT_TEST(TestParent);
	//CPPUNIT_TEST(TestParentT);
	//CPPUNIT_TEST(TestFollows);
	//CPPUNIT_TEST(TestFollowsT);
	CPPUNIT_TEST(TestUses);
	//CPPUNIT_TEST(TestModifies);
	//CPPUNIT_TEST(TestPattern);
	//CPPUNIT_TEST(TestSuchThatPattern);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestSelectAll();
	void TestParent();
	void TestParentT();
	void TestFollows();
	void TestFollowsT();
	void TestModifies();
	void TestUses();

	void TestPattern();

	void TestSuchThatPattern();
};

