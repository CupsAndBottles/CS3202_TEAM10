#include "ParserTest.h"
#include "AST\AST.h"

#include <fstream>

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ParserTest::setUp() {}
void ParserTest::tearDown() {}

ParserTest::ParserTest() {
}

AST parseSource(string filename) {
	ifstream sourceFile(string(TESTFILE_DIRECTORY).append(filename));
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	return Parser::Parse(buffer.str());
}

void ParserTest::TestSimpleAssignmentParsing() {
	AST testAST = parseSource("simpleAssignmentTest.txt");
	ProgramTNode program = testAST.getRootNode();
	ProcedureTNode procedure = program.getChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(1));

	CPPUNIT_ASSERT(procedure.getName() == "simpleAssignmentTest");
	CPPUNIT_ASSERT(firstStmt.getLHS().getContent() == "x");
	CPPUNIT_ASSERT(firstStmt.getRHS().getContent() == "1");
	CPPUNIT_ASSERT(secondStmt.getLHS().getContent() == "y");
	CPPUNIT_ASSERT(secondStmt.getLHS().getContent() == "x");

}

void ParserTest::TestAdditionParsing() {
	AST testAST = parseSource("additionTest.txt");
	ProgramTNode program = testAST.getRootNode();
	ProcedureTNode procedure = program.getChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(1));
	AssignmentTNode thirdStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(2));
	AssignmentTNode fourthStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(3));
	

	CPPUNIT_ASSERT(procedure.getName() == "additionTest");
	CPPUNIT_ASSERT(firstStmt.getLHS().getContent() == "x");
	CPPUNIT_ASSERT(secondStmt.getLHS().getContent() == "y");
	CPPUNIT_ASSERT(thirdStmt.getLHS().getContent() == "z");
	CPPUNIT_ASSERT(fourthStmt.getLHS().getContent() == "a");
}

void ParserTest::TestWhileParsing() {

}

void ParserTest::TestNestedWhileParsing() {

}

void ParserTest::TestParsing() {

}
