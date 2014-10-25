#include "QueryPreprocessorTest.h"
#include "QueryProcessor/QueryValidator.h"

void QueryPreprocessorTest::setUp() {
	
}
void QueryPreprocessorTest::tearDown() {}

void QueryPreprocessorTest::TestQueryPattern(){
/*
    bool result;
    QueryData queryData;

	result = QueryValidator::ValidateQuery("Select a pattern a(\"x\",_)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a Pattern a(\"x\",_)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a pAttern a(\"x\",_)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a pattern a(_)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a pattern a(\"x\",_,_)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a pattern a(\"x\",_\"y\"_)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a pattern a(\"x\",_\"y\")",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a pattern a(\"x\",_\"y\"__)",queryData);
	CPPUNIT_ASSERT(!result);
	*/
}

void QueryPreprocessorTest::TestQuerySuchthat(){
/*
	bool result;
    QueryData queryData;

	result = QueryValidator::ValidateQuery("Select a such that Follows(w,a)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a Such that Follows(w,a)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such Follows(w,a)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a that Follows(w,a)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such that",queryData);
	CPPUNIT_ASSERT(!result);
	*/
}

void QueryPreprocessorTest::TestComplexQuery(){
/*
	bool result;
    QueryData queryData;

	result = QueryValidator::ValidateQuery("Select a such that Follows(w,a) pattern a(\"x\",_)",queryData);
	CPPUNIT_ASSERT(result);

// test Follows:
	result = QueryValidator::ValidateQuery("Select a such that follows(w,a)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such that Follows*(w,a)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a such that Follows(w)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such that Follows(w,a,a)",queryData);
	CPPUNIT_ASSERT(!result);

// test Parent:
	result = QueryValidator::ValidateQuery("Select a such that Parent(w,a)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a such that Parent*(w,a)",queryData);
	CPPUNIT_ASSERT(result);

	result = QueryValidator::ValidateQuery("Select a such that parent(w,a)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such that Parent(w)",queryData);
	CPPUNIT_ASSERT(!result);

	result = QueryValidator::ValidateQuery("Select a such that Parent(w,a,w)",queryData);
	CPPUNIT_ASSERT(!result);

	*/

}