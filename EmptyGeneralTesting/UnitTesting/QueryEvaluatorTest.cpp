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

void QueryEvaluatorTest::TestHelperFunction()
{
	QueryEvaluator qe;
	std::string expr = "x";
	Pattern patternObj = qe.CreatePatternObject(expr); 

	CPPUNIT_ASSERT(patternObj.expr == "x");
	CPPUNIT_ASSERT(patternObj.leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern == NULL);



	expr = "111";
	patternObj = qe.CreatePatternObject(expr); 

	CPPUNIT_ASSERT(patternObj.expr == "111");
	CPPUNIT_ASSERT(patternObj.leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern == NULL);



	expr = "x+y";
	patternObj = qe.CreatePatternObject(expr); 

	CPPUNIT_ASSERT(patternObj.expr == "+");
	CPPUNIT_ASSERT(patternObj.leftPattern != NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern != NULL);
	CPPUNIT_ASSERT(patternObj.leftPattern->expr == "x");
	CPPUNIT_ASSERT(patternObj.leftPattern->leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.leftPattern->rightPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern->expr == "y");
	CPPUNIT_ASSERT(patternObj.rightPattern->leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern->rightPattern == NULL);


	expr = " 3 +  fnJw ";
	patternObj = qe.CreatePatternObject(expr); 

	CPPUNIT_ASSERT(patternObj.expr == "+");
	CPPUNIT_ASSERT(patternObj.leftPattern != NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern != NULL);
	CPPUNIT_ASSERT(patternObj.leftPattern->expr == "3");
	CPPUNIT_ASSERT(patternObj.leftPattern->leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.leftPattern->rightPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern->expr == "fnJw");
	CPPUNIT_ASSERT(patternObj.rightPattern->leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern->rightPattern == NULL);
}

void QueryEvaluatorTest::TestMergeResult()
{

}