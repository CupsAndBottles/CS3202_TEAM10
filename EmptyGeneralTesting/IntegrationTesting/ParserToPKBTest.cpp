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

// testOne uses the SIMPLE source code in simpleAssignmentTest.txt file
void ParserToPKBTest::testOneVarTable() {
	// initialise values for test
	Program testAST = parseSource("simpleAssignmentTest.txt");

	// check if VarTable has correct number of variables
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in VarTable", 2, VarTable::GetSize());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("first variable of VarTable", 0, VarTable::GetIndexOf("x"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("first variable of VarTable", 1, VarTable::GetIndexOf("y"));

}

void ParserToPKBTest::testOneModifiesUses() {
	// check if modifiesTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Modifies", 2, Modifies::SizeOfModifies());
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for first variable", Modifies::IsStmtModifiesVar(1, 0));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for second variable", Modifies::IsStmtModifiesVar(2, 1));

	// check if usesTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Uses", 1, Uses::SizeOfUses());
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for first variable", Uses::IsStmtUsingVar(2, 0));

}

void ParserToPKBTest::testOneParentsFollows() {
	// check if parentTable is not updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Parent", 0, Parent::SizeOfParent());

	// check if followsTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Follows", 1, Follows::SizeOfFollows());
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship", Follows::IsFollows(1, 2));

}

// testTwo uses the SIMPLE source code in whileTest.txt file
// testTwo uses the SIMPLE source code in nestedWhileTest.txt file
// testTwo uses the SIMPLE source code in additionTest.txt file

// insert other methods below here
// add a comment before each method to indicate its purpose