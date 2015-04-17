#include "UltimateTest2.h"
#include <cppunit\config\SourcePrefix.h>

#include <iostream>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(UltimateTest2);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void UltimateTest2::setUp() {
	Program::ClearAll();

	Parser::Parse(string(TESTFILE_DIRECTORY).append("Source.txt"));
}

void UltimateTest2::tearDown() {
	Program::ClearAll();
}


void UltimateTest2::TestPatternForIf() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;

	qd.ClearData();

	//query = "if i; Select i pattern i(\"z\",_)";

	//CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	//CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	//CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	//actualResultList.push_back("8");
	//actualResultList.push_back("24");
	//actualResultList.sort();

	//CPPUNIT_ASSERT(resultList == actualResultList);

	//qd.ClearData();
	//resultList.clear();
	//actualResultList.clear();
	//qe.ClearIntermediateResult();

	//query = "if i;variable v;Select v pattern i(v,_)";
	//std::cout << "\nTest query : " << query << "\n";

	//CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	//CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	//CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 1, int(resultList.size()));

	//actualResultList.clear();
	//actualResultList.push_back("z");
	//actualResultList.sort();

	//CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();
}

void UltimateTest2::TestCalls() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;

	qd.ClearData();

	query = "procedure p; Select p such that Calls(p,_)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	actualResultList.push_back("Solo");
	actualResultList.push_back("Duo");
	actualResultList.sort();

	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();


	//query = "procedure p; Select p such that Calls(\"Solo\",p)";

	//CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	//CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	//CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 3, int(resultList.size()));

	//actualResultList.push_back("Duo");
	//actualResultList.push_back("Trio");
	//actualResultList.push_back("Quartet");
	//actualResultList.sort();

	//CPPUNIT_ASSERT(resultList == actualResultList);

	//qd.ClearData();
	//resultList.clear();
	//actualResultList.clear();
	//qe.ClearIntermediateResult();
}

void UltimateTest2::TestCallsT() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;

	qd.ClearData();

	//query = "procedure p; Select p such that Calls*(\"Solo\",p)";

	//CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	//CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	//CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 3, int(resultList.size()));

	//actualResultList.push_back("Solo");
	//actualResultList.push_back("Duo");
	//actualResultList.push_back("Trio");
	//actualResultList.sort();

	//CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();
	
}
