#include "ParserTest.h"
#include "Program\Program.h"

#include <fstream>

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ParserTest::setUp() {}
void ParserTest::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);

ParserTest::ParserTest() {
}

Program parseSource(string filename) {
	ifstream sourceFile(string(TESTFILE_DIRECTORY).append(filename));
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	return Parser::Parse(buffer.str());
}

TNode& getLHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).getLHS();
}

TNode& getRHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).getRHS();
}

void ParserTest::TestSimpleAssignmentParsing() {
	Program testAST = parseSource("simpleAssignmentTest.txt");
	ProgramTNode program = testAST.getASTRootNode();
	ProcedureTNode procedure = program.getChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(1));

	CPPUNIT_ASSERT(procedure.getProcName() == "simpleAssignmentTest");

	CPPUNIT_ASSERT(firstStmt.getLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(firstStmt).getContent() == "x");
	CPPUNIT_ASSERT(getRHS(firstStmt).getContent() == "1");

	CPPUNIT_ASSERT(secondStmt.getLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(secondStmt).getContent() == "y");
	CPPUNIT_ASSERT(getRHS(secondStmt).getContent() == "x");

}

void ParserTest::TestAdditionParsing() {
	Program testAST = parseSource("additionTest.txt");
	ProgramTNode program = testAST.getASTRootNode();
	ProcedureTNode procedure = program.getChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(1));
	AssignmentTNode thirdStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(2));
	AssignmentTNode fourthStmt = dynamic_cast<AssignmentTNode&>(procedure.getProcedureBody().getChild(3));

	CPPUNIT_ASSERT(procedure.getProcName() == "additionTest");

	CPPUNIT_ASSERT(firstStmt.getLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(firstStmt).getContent() == "x");
	CPPUNIT_ASSERT(getRHS(firstStmt).getContent() == "+");
	CPPUNIT_ASSERT(getLHS(getRHS(firstStmt)).getContent() == "y");
	CPPUNIT_ASSERT(getRHS(getRHS(firstStmt)).getContent() == "z");

	CPPUNIT_ASSERT(secondStmt.getLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(secondStmt).getContent() == "y");
	CPPUNIT_ASSERT(getRHS(secondStmt).getContent() == "+");
	CPPUNIT_ASSERT(getLHS(getRHS(secondStmt)).getContent() == "z");
	CPPUNIT_ASSERT(getRHS(getRHS(secondStmt)).getContent() == "1");

	CPPUNIT_ASSERT(thirdStmt.getLineNumber() == 3);
	CPPUNIT_ASSERT(thirdStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(thirdStmt).getContent() == "z");
	CPPUNIT_ASSERT(getRHS(thirdStmt).getContent() == "+");
	CPPUNIT_ASSERT(getLHS(getRHS(thirdStmt)).getContent() == "2");
	CPPUNIT_ASSERT(getRHS(getRHS(thirdStmt)).getContent() == "3");

	CPPUNIT_ASSERT(fourthStmt.getLineNumber() == 4);
	CPPUNIT_ASSERT(fourthStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(fourthStmt).getContent() == "a");
	CPPUNIT_ASSERT(getRHS(fourthStmt).getContent() == "+");
	CPPUNIT_ASSERT(getLHS(getRHS(fourthStmt)).getContent() == "+");
	CPPUNIT_ASSERT(getRHS(getRHS(fourthStmt)).getContent() == "y");
	CPPUNIT_ASSERT(getLHS(getLHS(getRHS(fourthStmt))).getContent() == "x");
	CPPUNIT_ASSERT(getRHS(getLHS(getRHS(fourthStmt))).getContent() == "2");
}

void ParserTest::TestWhileParsing() {
	Program testAST = parseSource("whileTest.txt");
	ProgramTNode program = testAST.getASTRootNode();
	ProcedureTNode procedure = program.getChild(0);
	WhileTNode whileLoop = dynamic_cast<WhileTNode&>(procedure.getProcedureBody().getChild(0));
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(whileLoop.getBody().getChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(whileLoop.getBody().getChild(1));

	CPPUNIT_ASSERT(procedure.getProcName() == "whileTest");

	CPPUNIT_ASSERT(whileLoop.getLineNumber() == 1);
	CPPUNIT_ASSERT(whileLoop.getCondition().getContent() == "z");

	CPPUNIT_ASSERT(firstStmt.getLineNumber() == 2);
	CPPUNIT_ASSERT(firstStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(firstStmt).getContent() == "x");
	CPPUNIT_ASSERT(getRHS(firstStmt).getContent() == "2");

	CPPUNIT_ASSERT(secondStmt.getLineNumber() == 3);
	CPPUNIT_ASSERT(secondStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(secondStmt).getContent() == "y");
	CPPUNIT_ASSERT(getRHS(secondStmt).getContent() == "+");
	CPPUNIT_ASSERT(getLHS(getRHS(secondStmt)).getContent() == "y");
	CPPUNIT_ASSERT(getRHS(getRHS(secondStmt)).getContent() == "1");
}

void ParserTest::TestNestedWhileParsing() {
	Program testAST = parseSource("nestedWhileTest.txt");
	ProgramTNode program = testAST.getASTRootNode();
	ProcedureTNode procedure = program.getChild(0);
	WhileTNode firstWhileLoop = dynamic_cast<WhileTNode&>(procedure.getProcedureBody().getChild(0));
	WhileTNode secondWhileLoop = dynamic_cast<WhileTNode&>(firstWhileLoop.getBody().getChild(0));
	WhileTNode thirdWhileLoop = dynamic_cast<WhileTNode&>(secondWhileLoop.getBody().getChild(0));
	AssignmentTNode nestedStmt = dynamic_cast<AssignmentTNode&>(thirdWhileLoop.getBody().getChild(0));

	CPPUNIT_ASSERT(procedure.getProcName() == "nestedWhileParsing");

	CPPUNIT_ASSERT(firstWhileLoop.getLineNumber() == 1);
	CPPUNIT_ASSERT(firstWhileLoop.getCondition().getContent() == "x");

	CPPUNIT_ASSERT(secondWhileLoop.getLineNumber() == 2);
	CPPUNIT_ASSERT(secondWhileLoop.getCondition().getContent() == "y");

	CPPUNIT_ASSERT(thirdWhileLoop.getLineNumber() == 3);
	CPPUNIT_ASSERT(thirdWhileLoop.getCondition().getContent() == "z");

	CPPUNIT_ASSERT(nestedStmt.getLineNumber() == 4);
	CPPUNIT_ASSERT(nestedStmt.getOperator() == "=");
	CPPUNIT_ASSERT(getLHS(nestedStmt).getContent() == "x");
	CPPUNIT_ASSERT(getRHS(nestedStmt).getContent() == "0");
}
