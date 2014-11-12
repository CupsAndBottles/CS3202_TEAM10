#include "QueryEvaluatorToPKBTest.h"
#include <cppunit\config\SourcePrefix.h>

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

	StmtTypeTable::Insert(1,ASSIGN);
	StmtTypeTable::Insert(2,ASSIGN);
	StmtTypeTable::Insert(3,WHILE);
	StmtTypeTable::Insert(4,ASSIGN);
	StmtTypeTable::Insert(5,WHILE);
	StmtTypeTable::Insert(6,ASSIGN);
	StmtTypeTable::Insert(7,WHILE);
	StmtTypeTable::Insert(8,ASSIGN);
	StmtTypeTable::Insert(9,ASSIGN);

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

	Modifies::SetStmtModifiesVar(1,0);
	Modifies::SetStmtModifiesVar(2,1);
	Modifies::SetStmtModifiesVar(3,1);
	Modifies::SetStmtModifiesVar(3,3);
	Modifies::SetStmtModifiesVar(3,5);
	Modifies::SetStmtModifiesVar(4,3);
	Modifies::SetStmtModifiesVar(5,1);
	Modifies::SetStmtModifiesVar(6,1);
	Modifies::SetStmtModifiesVar(7,3);
	Modifies::SetStmtModifiesVar(8,3);
	Modifies::SetStmtModifiesVar(9,5);
	
	Uses::SetStmtUsesVar(2,0);
	Uses::SetStmtUsesVar(3,0);
	Uses::SetStmtUsesVar(3,2);
	Uses::SetStmtUsesVar(3,3);
	Uses::SetStmtUsesVar(3,4);
	Uses::SetStmtUsesVar(3,6);
	Uses::SetStmtUsesVar(3,7);
	Uses::SetStmtUsesVar(4,2);
	Uses::SetStmtUsesVar(4,0);
	Uses::SetStmtUsesVar(5,0);
	Uses::SetStmtUsesVar(5,3);
	Uses::SetStmtUsesVar(5,4);
	Uses::SetStmtUsesVar(6,4);
	Uses::SetStmtUsesVar(6,3);
	Uses::SetStmtUsesVar(7,3);
	Uses::SetStmtUsesVar(9,6);
	Uses::SetStmtUsesVar(9,7);
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


	qd.ClearData();
	resultList.clear();

	query = "assign a;while w;Select w such that Parent(w,w)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "assign a;stmt s;Select s such that Parent(s,a)";

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



	qd.ClearData();
	resultList.clear();

	query = "assign a;while w;stmt s;Select a such that Parent(w,s)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 6, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
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
	

	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Parent(s,_)";

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



	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Parent(_,s)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 6, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
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



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Parent(w,5)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 1, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Parent(3,s)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 4, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);;
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);;
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "prog_line n;Select n such that Parent(_,9)";

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



	qd.ClearData();
	resultList.clear();

	query = "prog_line n;Select n such that Parent(1,_)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());
	



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Parent(5,6)";

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



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Parent(_,_)";

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
}

void QueryEvaluatorToPKBTest::TestFollows()
{
	QueryData qd;
	QueryValidator qv;
	QueryEvaluator qe;
	std::list<std::string> resultList; 

	qd.ClearData();

	std::string query = "stmt s;while w;Select s such that Follows(w,s)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	//All assignment statement numbers
	std::list<std::string>::iterator it = resultList.begin();
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());


	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Follows(s,s)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "assign a1, a2;Select a1 such that Follows(a1,a2)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 1, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "assign a;while w1,w2;Select a such that Follows(w1,w2)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 6, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
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
	

	qd.ClearData();
	resultList.clear();

	query = "prog_line n;Select n such that Follows(n,_)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 5, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "prog_line n;Select n such that Follows(_,n)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 5, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Follows(s,2)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 1, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;prog_line n;Select w such that Follows(3,n)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "prog_line n;Select n such that Follows(_,1)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Follows(1,_)";

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
	


	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Follows(3,4)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Follows(_,_)";

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
}

void QueryEvaluatorToPKBTest::TestModifies()
{
	QueryData qd;
	QueryValidator qv;
	QueryEvaluator qe;
	std::list<std::string> resultList; 

	qd.ClearData();

	std::string query = "assign a;variable v;Select a such that Modifies(a,v)";

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

	
	qd.ClearData();
	resultList.clear();

	query = "stmt s;variable v;Select v such that Modifies(s,v)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 4, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "a");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "tEst");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "x");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "y");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());


	
	qd.ClearData();
	resultList.clear();

	query = "prog_line n1,n2;variable v;Select n1 such that Modifies(n2,v)";

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



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Modifies(w,_)";

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



	qd.ClearData();
	resultList.clear();

	query = "assign a;Select a such that Modifies(a,\"x\")";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 1, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "1");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Modifies(w,\"tEst\")";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "7");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "variable v;Select v such that Modifies(3,v)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 3, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "a");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "tEst");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "y");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Modifies(8,\"tEst\")";

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



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Modifies(1,_)";

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
}

void QueryEvaluatorToPKBTest::TestUses()
{
	QueryData qd;
	QueryValidator qv;
	QueryEvaluator qe;
	std::list<std::string> resultList; 

	qd.ClearData();

	std::string query = "assign a;variable v;Select a such that Uses(a,v)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 4, int(resultList.size()));

	//All assignment statement numbers
	std::list<std::string>::iterator it = resultList.begin();
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "6");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());

	
	qd.ClearData();
	resultList.clear();

	query = "prog_line n;variable v;Select v such that Uses(n,v)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 6, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "b");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "c");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "newVar");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "tEst");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "x");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "z");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());


	
	qd.ClearData();
	resultList.clear();

	query = "prog_line n1,n2;variable v;Select n1 such that Uses(n2,v)";

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



	qd.ClearData();
	resultList.clear();

	query = "stmt s;Select s such that Uses(s,_)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 7, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
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
	std::advance(it,1);;
	CPPUNIT_ASSERT(*it == "9");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "assign a;Select a such that Uses(a,\"x\")";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "2");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "4");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Uses(w,\"newVar\")";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 2, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(*it == "3");
	std::advance(it,1);
	CPPUNIT_ASSERT(*it == "5");
	std::advance(it,1);
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "variable v;Select v such that Uses(8,v)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Uses(3,\"tEst\")";

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



	qd.ClearData();
	resultList.clear();

	query = "while w;Select w such that Uses(1,_)";

	CPPUNIT_ASSERT_MESSAGE("Query is valid", qv.ValidateQuery(query, qd));
	CPPUNIT_ASSERT_MESSAGE("Query is successfully evaluated", qe.EvaluateQuery(qd, resultList));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Number of results is correct", 0, int(resultList.size()));

	//All assignment statement numbers
	it = resultList.begin();
	CPPUNIT_ASSERT(it == resultList.end());
}

void QueryEvaluatorToPKBTest::TestPattern()
{
}

void QueryEvaluatorToPKBTest::TestSuchThatPattern()
{
}
