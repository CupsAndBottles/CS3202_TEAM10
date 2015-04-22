#pragma once

#include "PatternMatcherTest.h"
#include "..\SPA\Parser\Parser.h"
#include "..\SPA\Parser\Tokenizer.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\ConstTable.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\QueryProcessor\PatternMatcher.h"

TNode* PatternMatcherTest::ParseExpr(string expr) {
	// use parser to construct a tree to test with
	// kinda hacky
	Program::ClearAll();
	Parser parser(Tokenizer::Tokenize(expr.append(";"))); // need to append end of stmt
	parser.currentLineNumber = 1;
	TNode* exprTree = parser.ParseExpr(false);
	Uses::ClearData();
	Modifies::ClearData();
	VarTable::ClearData();
	ConstTable::ClearData();
	return exprTree;
}

void PatternMatcherTest::setUp() {
	Program::ClearData();
}

void PatternMatcherTest::tearDown() {
	Program::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(PatternMatcherTest);

PatternMatcherTest::PatternMatcherTest() {
	// empty body
}

void PatternMatcherTest::testCreatePatternObject() {
	std::string expr = "x";
	Pattern patternObj = PatternMatcher::CreatePatternObject(expr);

	CPPUNIT_ASSERT(patternObj.expr == "x");
	CPPUNIT_ASSERT(patternObj.leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern == NULL);



	expr = "111";
	patternObj = PatternMatcher::CreatePatternObject(expr);

	CPPUNIT_ASSERT(patternObj.expr == "111");
	CPPUNIT_ASSERT(patternObj.leftPattern == NULL);
	CPPUNIT_ASSERT(patternObj.rightPattern == NULL);



	expr = "x+y";
	patternObj = PatternMatcher::CreatePatternObject(expr);

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
	patternObj = PatternMatcher::CreatePatternObject(expr);

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

void PatternMatcherTest::matchSingleVariable() {
	string expr = "x";
	TNode* exprTree = ParseExpr(expr);
	Program::ClearAll();

	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), false));
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("y", nullptr, nullptr), true));
}

void PatternMatcherTest::matchExprsWithTwoVariables() {
	string expr = "x + y";
	TNode* exprTree = ParseExpr(expr);
	Program::ClearAll();
	
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), false));
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("y", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("y", nullptr, nullptr), false));

	Pattern xPlusY("+", new Pattern("x", nullptr, nullptr), new Pattern("y", nullptr, nullptr));

	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, xPlusY, true));
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, xPlusY, false));
}

void PatternMatcherTest::matchExprsWithMultipleVariables() {
	string expr = "x + 1 + y";
	TNode* exprTree = ParseExpr(expr);
	Program::ClearAll();

	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("x", nullptr, nullptr), false));
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("y", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("y", nullptr, nullptr), false));
	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("1", nullptr, nullptr), true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, Pattern("1", nullptr, nullptr), false));

	Pattern xPlus1("+", new Pattern("x", nullptr, nullptr), new Pattern("1", nullptr, nullptr));
	Pattern xPlusY("+", new Pattern("x", nullptr, nullptr), new Pattern("y", nullptr, nullptr));
	Pattern yPlus1("+", new Pattern("y", nullptr, nullptr), new Pattern("1", nullptr, nullptr));

	CPPUNIT_ASSERT_EQUAL(true, PatternMatcher::MatchPatternAtLeaves(exprTree, xPlus1, true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, xPlusY, true));
	CPPUNIT_ASSERT_EQUAL(false, PatternMatcher::MatchPatternAtLeaves(exprTree, yPlus1, true));
}


void PatternMatcherTest::matchNewOperators() {
	string expr = "a + b * c + d";
	TNode* exprTree = ParseExpr(expr);
	Program::ClearAll();

	string queryStr = "a + b * c + d";
	Pattern patternObj = PatternMatcher::CreatePatternObject(queryStr);

	CPPUNIT_ASSERT(PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, true));

	queryStr = "b * c";
	patternObj = PatternMatcher::CreatePatternObject(queryStr);

	CPPUNIT_ASSERT(PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, true));
	CPPUNIT_ASSERT(!PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, false));

	queryStr = "b + c";
	patternObj = PatternMatcher::CreatePatternObject(queryStr);

	CPPUNIT_ASSERT(!PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, true));
	CPPUNIT_ASSERT(!PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, false));

	queryStr = "a + b * c";
	patternObj = PatternMatcher::CreatePatternObject(queryStr);

	CPPUNIT_ASSERT(PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, true));
	CPPUNIT_ASSERT(!PatternMatcher::MatchPatternAtLeaves(exprTree, patternObj, false));
}
