#include "QueryEvaluatorTest.h"
#include <cppunit/config/SourcePrefix.h>
#include "..\SPA\QueryProcessor\QueryEvaluator.h"
#include "..\SPA\Program\Program.h"

void QueryEvaluatorTest::setUp() {
	Program::ClearAll();
}

void QueryEvaluatorTest::tearDown() {
	Program::ClearAll();
}

CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorTest);

QueryEvaluatorTest::QueryEvaluatorTest(void){}

void QueryEvaluatorTest::TestMergeResult()
{

}