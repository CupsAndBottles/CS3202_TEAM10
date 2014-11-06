#include <cppunit\config\SourcePrefix.h>

#include "ParserToPKBTest.h"

#include "Parser\Parser.h"
#include "PKB\VarTable.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\Follows.h"
#include "PKB\Parent.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "Program\Program.h"

#include <iostream>
#include <string>
#include <stdint.h>

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ParserToPKBTest::setUp() { 
	// empty body
}

void ParserToPKBTest::tearDown() {
	// empty body
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserToPKBTest);

void ParserToPKBTest::testNothing() {
	CPPUNIT_ASSERT_EQUAL_MESSAGE("simple dummy test", 0, 0);
}

Program parseSource(string filename) {
	ifstream sourceFile(string(TESTFILE_DIRECTORY).append(filename));
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	return Parser::Parse(buffer.str());
}

void ParserToPKBTest::testOne() {
	// initialise values for test
	Program testAST = parseSource("simpleAssignmentTest.txt");

	// check if VarTable has correct number of variables
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in VarTable", 2, VarTable::GetSize());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("first variable of vartable", 0, VarTable::GetIndexOf("x"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("first variable of vartable", 1, VarTable::GetIndexOf("y"));

	// check if modifies and uses tables are updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Modifies", 2, Modifies::SizeOfModifies());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Uses", 1, Uses::SizeOfUses());
	

}

// insert other methods below here
// add a comment before each method to indicate its purpose