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

CPPUNIT_TEST_SUITE_REGISTRATION(ParserToPKBTest);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ParseSource(string filename) {
	ifstream sourceFile(string(TESTFILE_DIRECTORY).append(filename));
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	sourceFile.close();
	Parser::Parse(buffer.str());
}

void ParserToPKBTest::setUp() { 
	Program::ClearData();
	ParseSource("pkbTest.txt");
}

void ParserToPKBTest::tearDown() {
	// empty body
}



void ParserToPKBTest::TestNothing() {
	CPPUNIT_ASSERT_EQUAL_MESSAGE("simple dummy test", 0, 0);
}

// testTwo uses the SIMPLE source code in whileTest.txt file
// testTwo uses the SIMPLE source code in nestedWhileTest.txt file
// testTwo uses the SIMPLE source code in additionTest.txt file

// insert other methods below here
void ParserToPKBTest::TestVarTable() {
	// check if VarTable has correct number of variables
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in VarTable", 8, VarTable::GetSize());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("1st variable of VarTable", 0, VarTable::GetIndexOf("x"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("2nd variable of VarTable", 1, VarTable::GetIndexOf("y"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("3rd variable of VarTable", 2, VarTable::GetIndexOf("z"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("4th variable of VarTable", 3, VarTable::GetIndexOf("tEst"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("5th variable of VarTable", 4, VarTable::GetIndexOf("newVar"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("6th variable of VarTable", 5, VarTable::GetIndexOf("a"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("7th variable of VarTable", 6, VarTable::GetIndexOf("b"));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("8th variable of VarTable", 7, VarTable::GetIndexOf("c"));
}

void ParserToPKBTest::TestModifies() {
	// check if modifiesTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Modifies", 6, Modifies::SizeOfModifies());
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 1st variable", Modifies::IsStmtModifyingVar(1, 0));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 2nd variable", Modifies::IsStmtModifyingVar(2, 1));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 3rd variable", Modifies::IsStmtModifyingVar(4, 3));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 4th variable", Modifies::IsStmtModifyingVar(6, 1));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 5th variable", Modifies::IsStmtModifyingVar(8, 3));
	CPPUNIT_ASSERT_MESSAGE("test correct Modifies relationship for 6th variable", Modifies::IsStmtModifyingVar(9, 5));

	CPPUNIT_ASSERT(Modifies::GetStmtModifyingVar(VarTable::GetIndexOf("a"))[0] == 9);
	//CPPUNIT_ASSERT(Modifies::GetStmtModifyingVar(VarTable::GetIndexOf("tEst"))[0] == 6);
	CPPUNIT_ASSERT(Modifies::GetStmtModifyingVar(VarTable::GetIndexOf("tEst"))[1] == 8);
	CPPUNIT_ASSERT(Modifies::GetStmtModifyingVar(VarTable::GetIndexOf("tEst"))[1] == 7);
}

void ParserToPKBTest::TestUses() {
	// check if usesTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Uses", 7, Uses::SizeOfUses());
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 1st variable", Uses::IsStmtUsingVar(2, 0));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 2nt variable", Uses::IsStmtUsingVar(3, 2));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 3rd variable", Uses::IsStmtUsingVar(4, 2));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 4th variable", Uses::IsStmtUsingVar(4, 0));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 5th variable", Uses::IsStmtUsingVar(5, 0));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 6th variable", Uses::IsStmtUsingVar(6, 4));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 7th variable", Uses::IsStmtUsingVar(6, 3));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 8th variable", Uses::IsStmtUsingVar(7, 3));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 9th variable", Uses::IsStmtUsingVar(9, 6));
	CPPUNIT_ASSERT_MESSAGE("test correct Uses relationship for 10th variable", Uses::IsStmtUsingVar(9, 7));
}

void ParserToPKBTest::TestParent() {
	// check if parentTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Parent", 6, Parent::SizeOfParent());
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 1st variable", Parent::IsParent(3, 4));
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 2nd variable", Parent::IsParent(3, 5));
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 3rd variable", Parent::IsParent(3, 7));
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 4th variable", Parent::IsParent(3, 9));
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 5th variable", Parent::IsParent(5, 6));
	CPPUNIT_ASSERT_MESSAGE("test correct Parent relationship for 6th variable", Parent::IsParent(7, 8));

	CPPUNIT_ASSERT_MESSAGE("test correct ParentT relationship for 3th variable", Parent::IsParentT(3, 6));
	CPPUNIT_ASSERT_MESSAGE("test correct ParentT relationship for 3th variable", Parent::IsParentT(3, 7));
	CPPUNIT_ASSERT_MESSAGE("test correct ParentT relationship for 3th variable", Parent::IsParentT(3, 8));
	//CPPUNIT_ASSERT_MESSAGE("test correct ParentT relationship for 3th variable", Parent::IsParentT(2, 9));

}

void ParserToPKBTest::TestFollows() {
	// check if followsTable is updated
	CPPUNIT_ASSERT_EQUAL_MESSAGE("number of variables in Follows", 5, Follows::SizeOfFollows());
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship for 1st variable", Follows::IsFollows(1, 2));
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship for 2nd variable", Follows::IsFollows(2, 3));
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship for 3rd variable", Follows::IsFollows(4, 5));
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship for 4th variable", Follows::IsFollows(5, 7));
	CPPUNIT_ASSERT_MESSAGE("test correct Follows relationship for 5th variable", Follows::IsFollows(7, 9));

	CPPUNIT_ASSERT(Follows::IsFollowsT(1, 3));
	CPPUNIT_ASSERT(Follows::IsFollowsT(1, 2));
	CPPUNIT_ASSERT(Follows::IsFollowsT(4, 9));

	//CPPUNIT_ASSERT(Follows::IsFollowsT(4, 6));
	//CPPUNIT_ASSERT(Follows::IsFollowsT(9, 4));

}

void ParserToPKBTest::TestStmtTypeTable() {
	// check if StmtTypeTable is updated
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 1st stmt", StmtTypeTable::CheckIfStmtOfType(1, ASSIGN));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 2nd stmt", StmtTypeTable::CheckIfStmtOfType(2, ASSIGN));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 3rd stmt", StmtTypeTable::CheckIfStmtOfType(3, WHILE));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 4th stmt", StmtTypeTable::CheckIfStmtOfType(4, ASSIGN));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 5th stmt", StmtTypeTable::CheckIfStmtOfType(5, WHILE));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 6th stmt", StmtTypeTable::CheckIfStmtOfType(6, ASSIGN));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 7th stmt", StmtTypeTable::CheckIfStmtOfType(7, WHILE));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 8th stmt", StmtTypeTable::CheckIfStmtOfType(8, ASSIGN));
	CPPUNIT_ASSERT_MESSAGE("test correct typing for 9th stmt", StmtTypeTable::CheckIfStmtOfType(9, ASSIGN));
}

// add a comment before each method to indicate its purpose