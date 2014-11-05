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

TNode& GetLHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).GetLHS();
}

TNode& GetRHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).GetRHS();
}

void ParserTest::TestSimpleAssignmentParsing() {
	Program testAST = parseSource("simpleAssignmentTest.txt");
	ProgramTNode program = testAST.GetASTRootNode();
	ProcedureTNode procedure = program.GetChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(1));

	CPPUNIT_ASSERT(procedure.GetProcName() == "simpleAssignmentTest");

	CPPUNIT_ASSERT(firstStmt.GetLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(firstStmt).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(firstStmt).GetContent() == "1");

	CPPUNIT_ASSERT(secondStmt.GetLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(secondStmt).GetContent() == "y");
	CPPUNIT_ASSERT(GetRHS(secondStmt).GetContent() == "x");

}

void ParserTest::TestAdditionParsing() {
	Program testAST = parseSource("additionTest.txt");
	ProgramTNode program = testAST.GetASTRootNode();
	ProcedureTNode procedure = program.GetChild(0);
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(1));
	AssignmentTNode thirdStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(2));
	AssignmentTNode fourthStmt = dynamic_cast<AssignmentTNode&>(procedure.GetProcedureBody().GetChild(3));

	CPPUNIT_ASSERT(procedure.GetProcName() == "additionTest");

	CPPUNIT_ASSERT(firstStmt.GetLineNumber() == 1);
	CPPUNIT_ASSERT(firstStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(firstStmt).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(firstStmt).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(firstStmt)).GetContent() == "y");
	CPPUNIT_ASSERT(GetRHS(GetRHS(firstStmt)).GetContent() == "z");

	CPPUNIT_ASSERT(secondStmt.GetLineNumber() == 2);
	CPPUNIT_ASSERT(secondStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(secondStmt).GetContent() == "y");
	CPPUNIT_ASSERT(GetRHS(secondStmt).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(secondStmt)).GetContent() == "z");
	CPPUNIT_ASSERT(GetRHS(GetRHS(secondStmt)).GetContent() == "1");

	CPPUNIT_ASSERT(thirdStmt.GetLineNumber() == 3);
	CPPUNIT_ASSERT(thirdStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(thirdStmt).GetContent() == "z");
	CPPUNIT_ASSERT(GetRHS(thirdStmt).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(thirdStmt)).GetContent() == "2");
	CPPUNIT_ASSERT(GetRHS(GetRHS(thirdStmt)).GetContent() == "3");

	CPPUNIT_ASSERT(fourthStmt.GetLineNumber() == 4);
	CPPUNIT_ASSERT(fourthStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(fourthStmt).GetContent() == "a");
	CPPUNIT_ASSERT(GetRHS(fourthStmt).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(fourthStmt)).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetRHS(fourthStmt)).GetContent() == "y");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetRHS(fourthStmt))).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetRHS(fourthStmt))).GetContent() == "2");
}

void ParserTest::TestWhileParsing() {
	Program testAST = parseSource("whileTest.txt");
	ProgramTNode program = testAST.GetASTRootNode();
	ProcedureTNode procedure = program.GetChild(0);
	WhileTNode whileLoop = dynamic_cast<WhileTNode&>(procedure.GetProcedureBody().GetChild(0));
	AssignmentTNode firstStmt = dynamic_cast<AssignmentTNode&>(whileLoop.GetBody().GetChild(0));
	AssignmentTNode secondStmt = dynamic_cast<AssignmentTNode&>(whileLoop.GetBody().GetChild(1));

	CPPUNIT_ASSERT(procedure.GetProcName() == "whileTest");

	CPPUNIT_ASSERT(whileLoop.GetLineNumber() == 1);
	CPPUNIT_ASSERT(whileLoop.GetCondition().GetContent() == "z");

	CPPUNIT_ASSERT(firstStmt.GetLineNumber() == 2);
	CPPUNIT_ASSERT(firstStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(firstStmt).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(firstStmt).GetContent() == "2");

	CPPUNIT_ASSERT(secondStmt.GetLineNumber() == 3);
	CPPUNIT_ASSERT(secondStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(secondStmt).GetContent() == "y");
	CPPUNIT_ASSERT(GetRHS(secondStmt).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(secondStmt)).GetContent() == "y");
	CPPUNIT_ASSERT(GetRHS(GetRHS(secondStmt)).GetContent() == "1");
}

void ParserTest::TestNestedWhileParsing() {
	Program testAST = parseSource("nestedWhileTest.txt");
	ProgramTNode program = testAST.GetASTRootNode();
	ProcedureTNode procedure = program.GetChild(0);
	WhileTNode firstWhileLoop = dynamic_cast<WhileTNode&>(procedure.GetProcedureBody().GetChild(0));
	WhileTNode secondWhileLoop = dynamic_cast<WhileTNode&>(firstWhileLoop.GetBody().GetChild(0));
	WhileTNode thirdWhileLoop = dynamic_cast<WhileTNode&>(secondWhileLoop.GetBody().GetChild(0));
	AssignmentTNode nestedStmt = dynamic_cast<AssignmentTNode&>(thirdWhileLoop.GetBody().GetChild(0));

	CPPUNIT_ASSERT(procedure.GetProcName() == "nestedWhileParsing");

	CPPUNIT_ASSERT(firstWhileLoop.GetLineNumber() == 1);
	CPPUNIT_ASSERT(firstWhileLoop.GetCondition().GetContent() == "x");

	CPPUNIT_ASSERT(secondWhileLoop.GetLineNumber() == 2);
	CPPUNIT_ASSERT(secondWhileLoop.GetCondition().GetContent() == "y");

	CPPUNIT_ASSERT(thirdWhileLoop.GetLineNumber() == 3);
	CPPUNIT_ASSERT(thirdWhileLoop.GetCondition().GetContent() == "z");

	CPPUNIT_ASSERT(nestedStmt.GetLineNumber() == 4);
	CPPUNIT_ASSERT(nestedStmt.GetOperator() == "=");
	CPPUNIT_ASSERT(GetLHS(nestedStmt).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(nestedStmt).GetContent() == "0");
}
