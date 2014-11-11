#include "QueryEvaluatorToPKBTest.h"
#include <cppunit\config\SourcePrefix.h>

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

#include <iostream>
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(QueryEvaluatorToPKBTest);

void QueryEvaluatorToPKBTest::setUp() { 
	VarTable::ClearData();
	StmtTypeTable::ClearData();
	Parent::ClearData();
	Follows::ClearData();
	Uses::ClearData();
	Modifies::ClearData();
	
	VarTable::InsertVar("x");
	VarTable::InsertVar("y");
	VarTable::InsertVar("z");
	VarTable::InsertVar("tEst");
	VarTable::InsertVar("newVar");
	VarTable::InsertVar("a");
	VarTable::InsertVar("b");
	VarTable::InsertVar("c");

	StmtTypeTable::insert(1,ASSIGN);
	StmtTypeTable::insert(2,ASSIGN);
	StmtTypeTable::insert(3,WHILE);
	StmtTypeTable::insert(4,ASSIGN);
	StmtTypeTable::insert(5,WHILE);
	StmtTypeTable::insert(6,ASSIGN);
	StmtTypeTable::insert(7,WHILE);
	StmtTypeTable::insert(8,ASSIGN);
	StmtTypeTable::insert(9,ASSIGN);

	Parent::SetParent(3,4);
	Parent::SetParent(3,5);
	Parent::SetParent(3,7);
	Parent::SetParent(3,9);
	Parent::SetParent(5,6);
	Parent::SetParent(7,8);

	Follows::SetFollows(1,2);
	Follows::SetFollows(2,3);
	Follows::SetFollows(4,5);
	Follows::SetFollows(5,7);
	Follows::SetFollows(7,9);
}

void QueryEvaluatorToPKBTest::tearDown() {}

void QueryEvaluatorToPKBTest::TestSelectAll()
{
	QueryData qd;
	QueryValidator qv;
	QueryEvaluator qe;
	std::list<std::string> resultList; 

	qd.ClearData();

	std::string query = "assign a;while w;Select a";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 6, int(resultList.size()));

	//All assignment statement numbers
	std::list<std::string>::iterator it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "6");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "8");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	resultList.clear();
	qd.ClearData();

	query = "assign a;while w;Select w";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 3, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());


	resultList.clear();
	qd.ClearData();

	query = "assign a;while w;stmt s;Select s";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 9, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "6");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "8");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	resultList.clear();
	qd.ClearData();

	query = "assign a;while w;prog_line p;Select p";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 9, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "6");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "8");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	resultList.clear();
	qd.ClearData();

	query = "variable v;Select v";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 8, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "x");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "y");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "z");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "tEst");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "newVar");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "a");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "b");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "c");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());
}

void QueryEvaluatorToPKBTest::TestParent()
{
	QueryData qd;
	QueryValidator qv;
	QueryEvaluator qe;
	std::list<std::string> resultList; 

	qd.ClearData();

	std::string query = "assign a;while w;Select a such that Parent(w,a)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 4, int(resultList.size()));

	//All assignment statement numbers
	std::list<std::string>::iterator it = resultList.begin();
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "6");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "8");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());

}