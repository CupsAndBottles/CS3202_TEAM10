#include "UltimateWithAndTest.h"
#include <cppunit\config\SourcePrefix.h>

#include <iostream>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(UltimateWithAndTest);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void UltimateWithAndTest::setUp() {
	Program::ClearAll();

	Parser::Parse(string(TESTFILE_DIRECTORY).append("ultimateWithAndTest.txt"));
}

void UltimateWithAndTest::tearDown() {
	Program::ClearAll();
}
void UltimateWithAndTest::WithAndTest1() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;
	qd.ClearData();
	
	query = "assign a;stmt s1; Select a such that Modifies(a,\"b\") and Affects(a,s1)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	actualResultList.push_back("2");
	actualResultList.push_back("13");

	resultList.sort();
	actualResultList.sort();
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "assign a;stmt s1; Select a such that Affects(a,s1) and Modifies(a,\"x\")";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	actualResultList.push_back("2");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "assign a;stmt s1; Select a such that Affects(a,s1) and Modifies(a,\"a\") with s1.stmt#=25";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	actualResultList.push_back("19");
	CPPUNIT_ASSERT(resultList == actualResultList);

}

void UltimateWithAndTest::WithAndTest2() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;
	qd.ClearData();
	
	query = "assign a; assign ax; stmt s; Select s such that Affects(a,ax) and Affects(a,s) with Uses(s, \"a\") and pattern a(_,_)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	actualResultList.push_back("1");
	actualResultList.push_back("3");
	actualResultList.push_back("4");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "assign ax; stmt s; stmt s1; Select s such that Affects(s,ax) with Uses(s, \"a\")";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	actualResultList.push_back("3");
	actualResultList.push_back("19");
	actualResultList.push_back("23");
	actualResultList.push_back("27");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();
}

void UltimateWithAndTest::WithAndTest3() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;
	qd.ClearData();
	
	query = "assign a;stmt s1; Select a such that Modifies(a,\"x\") and Modifies(s1,a)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "assign a;stmt s1; Select s1 such that Uses(a,\"x\") and Uses(s1,a)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));
	
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();
	
	query = "assign a;stmt s1; Select a such that Modifies(a,\"x\") and a.stmt#=1";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	actualResultList.push_back("1");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "constant c;stmt s1; assign a; var v; Select a such that Uses(s1,c) and Modifies(s1, v) with Uses(a, c)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));
	
	actualResultList.push_back("1");
	actualResultList.push_back("2");
	actualResultList.push_back("4");
	actualResultList.push_back("5");
	actualResultList.push_back("7");
	actualResultList.push_back("8");
	actualResultList.push_back("13");
	actualResultList.push_back("14");
	actualResultList.push_back("16");
	actualResultList.push_back("19");
	actualResultList.push_back("20");
	actualResultList.push_back("22");
	actualResultList.push_back("26");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

}

void UltimateWithAndTest::WithAndTest4() {
	QueryData qd;
	QueryPreProcessor qv;
	QueryEvaluator qe;
	std::string query;
	std::list<std::string> resultList;
	std::list<std::string> actualResultList;
	qd.ClearData();
	
	query = "assign a;stmt s1; procedure p; Select p such that Modifies(a,\"x\") and Modifies(s1,a) with p.procname=a.stmt#";
	CPPUNIT_ASSERT_MESSAGE("Query is invalid", !qv.ValidateQuery(query, qd));

	query = "stmt s1; procedure p; Select s1 such that Modifies(p,\"c\") with Calls(s1, p)";
	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));
	
	actualResultList.push_back("10");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

	query = "stmt s; var v; constant co; assign a; Select a such that pattern a(v, _\"*\"_) with Uses(a, co) and co.value=s.stmt# and Modifies(s, \"abc\")";

	actualResultList.push_back("2");
	CPPUNIT_ASSERT(resultList == actualResultList);

	qd.ClearData();
	resultList.clear();
	actualResultList.clear();
	qe.ClearIntermediateResult();

}