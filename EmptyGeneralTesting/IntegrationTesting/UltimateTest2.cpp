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
	//QueryData qd;
	//QueryPreProcessor qv;
	//QueryEvaluator qe;
	//std::string query;
	//std::list<std::string> resultList;
	//std::list<std::string> actualResultList;

	//qd.ClearData();

	//query = "assign a;while w;Select a such that Parent(w,a)";

	//CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	//CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	//CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 16, int(resultList.size()));

	//actualResultList.push_back("7");
	//actualResultList.push_back("8");
	//actualResultList.push_back("10");
	//actualResultList.push_back("12");
	//actualResultList.push_back("13");
	//actualResultList.push_back("14");
	//actualResultList.push_back("16");
	//actualResultList.push_back("17");
	//actualResultList.push_back("18");
	//actualResultList.push_back("19");
	//actualResultList.push_back("20");
	//actualResultList.push_back("22");
	//actualResultList.push_back("23");
	//actualResultList.push_back("25");
	//actualResultList.push_back("26");
	//actualResultList.push_back("27");
	//actualResultList.sort();

	//CPPUNIT_ASSERT(resultList == actualResultList);

	//qd.ClearData();
	//resultList.clear();
	//actualResultList.clear();
	//qe.ClearIntermediateResult();
}

void UltimateTest2::TestCalls() {
	
}

void UltimateTest2::TestCallsT() {
	
}
