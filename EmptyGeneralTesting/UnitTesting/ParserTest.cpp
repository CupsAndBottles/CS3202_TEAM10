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

	CPPUNIT_ASSERT(firstStmt.getLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.getOperator() == "=");
	CPPUNIT_ASSERT(firstStmt.getLHS().getContent() == "x");
	CPPUNIT_ASSERT(firstStmt.getRHS().getContent() == "1");

	CPPUNIT_ASSERT(secondStmt.getLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.getOperator() == "=");
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

	CPPUNIT_ASSERT(firstStmt.getLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.getOperator() == "=");
	CPPUNIT_ASSERT(firstStmt.getLHS().getContent() == "x");
	CPPUNIT_ASSERT(firstStmt.getRHS().getContent() == "+");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(firstStmt.getRHS()).getLHS().getContent() == "y");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(firstStmt.getRHS()).getRHS().getContent() == "z");

	CPPUNIT_ASSERT(secondStmt.getLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.getOperator() == "=");
	CPPUNIT_ASSERT(secondStmt.getLHS().getContent() == "y");
	CPPUNIT_ASSERT(secondStmt.getRHS().getContent() == "+");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(secondStmt.getRHS()).getLHS().getContent() == "z");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(secondStmt.getRHS()).getRHS().getContent() == "1");

	CPPUNIT_ASSERT(thirdStmt.getLineNumber() == 3);
	CPPUNIT_ASSERT(thirdStmt.getOperator() == "=");
	CPPUNIT_ASSERT(thirdStmt.getLHS().getContent() == "z");
	CPPUNIT_ASSERT(thirdStmt.getRHS().getContent() == "+");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(thirdStmt.getRHS()).getLHS().getContent() == "2");
	CPPUNIT_ASSERT(dynamic_cast<BinaryTNode&>(thirdStmt.getRHS()).getRHS().getContent() == "3");

	CPPUNIT_ASSERT(fourthStmt.getLineNumber() == 4);
	CPPUNIT_ASSERT(fourthStmt.getOperator() == "=");
	CPPUNIT_ASSERT(fourthStmt.getLHS().getContent() == "a");

}

void ParserTest::TestWhileParsing() {

}

void ParserTest::TestNestedWhileParsing() {

}

void ParserTest::TestParsing() {

}
