#pragma once

#include <cppunit/config/SourcePrefix.h>

#include "QueryDataTest.h"
#include "QueryProcessor/QueryData.h"

#include <vector>

using namespace std;

void QueryDataTest::setUp() {};
void QueryDataTest::tearDown() {};

CPPUNIT_TEST_SUITE_REGISTRATION(QueryDataTest);

void QueryDataTest::testInsertQueryData() 
{
	/*QueryData qd;

	qd.InsertDeclaration("assign","a");
	qd.InsertDeclaration("procedure","p");
	qd.InsertSelect("assign", "a");
	qd.InsertPattern("a", "_", "\"x+y\"");
	qd.InsertSuchThat("Modifies", "a", "v");
	qd.InsertWith("p.procName", "\"one\"");

	std::vector<Declaration> declarations = qd.GetDeclarations();
	CPPUNIT_ASSERT(declarations.at(0).type == "assign");
	CPPUNIT_ASSERT(declarations.at(0).synonym == "a");
	CPPUNIT_ASSERT(declarations.at(1).type == "procedure");
	CPPUNIT_ASSERT(declarations.at(1).synonym == "p");

	std::vector<SelectClause> selects = qd.GetSelects();
	CPPUNIT_ASSERT(selects.at(0).type == "assign");
	CPPUNIT_ASSERT(selects.at(0).synonym == "a");

	std::vector<PatternClause> patterns = qd.GetPatterns();
	CPPUNIT_ASSERT(patterns.at(0).type == "a");
	CPPUNIT_ASSERT(patterns.at(0).arg1 == "_");
	CPPUNIT_ASSERT(patterns.at(0).arg2 == "\"x+y\"");

	std::vector<SuchThatClause> suchThats = qd.GetSuchThats();
	CPPUNIT_ASSERT(suchThats.at(0).condition == "Modifies");
	CPPUNIT_ASSERT(suchThats.at(0).arg1 == "a");
	CPPUNIT_ASSERT(suchThats.at(0).arg2 == "v");

	std::vector<WithClause> withs = qd.GetWiths();
	CPPUNIT_ASSERT(withs.at(0).arg1 == "p.procName");
	CPPUNIT_ASSERT(withs.at(0).arg2 == "\"one\"");

	bool exist = qd.IsSynonymExist("a","assign");
	CPPUNIT_ASSERT(exist == true);

	exist = qd.IsSynonymExist("b","assign");
	CPPUNIT_ASSERT(exist == false);

	std::string list[] = {"while","if","prog_line","call","stmt","assign","procedure"};
	std::vector<std::string> typeList(list, list + 7);

	exist = qd.IsSynonymExist("a",list);
	CPPUNIT_ASSERT(exist == true);

	exist = qd.IsSynonymExist("p",list);
	CPPUNIT_ASSERT(exist == true);

	exist = qd.IsSynonymExist("c",list);
	CPPUNIT_ASSERT(exist == false);

	std::string list2[] = {"while","if","prog_line","procedure"};
	std::vector<std::string> typeList2(list2, list2 + 4);

	exist = qd.IsSynonymExist("a",typeList2);
	CPPUNIT_ASSERT(exist == false);

	exist = qd.IsSynonymExist("p",typeList2);
	CPPUNIT_ASSERT(exist == true);*/
}


/*
void InsertDeclaration(std::string, std::string);
void InsertSelect(std::string, std::string);
void InsertPattern(std::string, std::string, std::string);
void InsertSuchThat(std::string, std::string, std::string);
void InsertWith(std::string, std::string);

std::vector<Declaration> GetDeclarations();
std::vector<SelectClause> GetSelects();		//if empty = select BOOLEAN
std::vector<SuchThatClause> GetSuchThats();
std::vector<PatternClause> GetPatterns();
std::vector<WithClause> GetWiths();

static bool IsSynonymExist(std::string, std::string);
static bool IsSynonymExist(std::string, std::string *);
static bool IsSynonymExist(std::string, std::vector<std::string>);
*/