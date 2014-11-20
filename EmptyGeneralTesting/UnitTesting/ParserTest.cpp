#include "ParserTest.h"
#include "..\SPA\Program\Program.h"

#include <fstream>

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ParserTest::setUp() {}
void ParserTest::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserTest);

ParserTest::ParserTest() {
}

void ParseSource(string filename) {
	Parser::Parse(string(TESTFILE_DIRECTORY).append(filename));
}

TNode& GetLHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).GetLHS();
}

TNode& GetRHS(TNode& node) {
	return dynamic_cast<BinaryTNode&>(node).GetRHS();
}

void ParserTest::TestSimpleAssignmentParsing() {
	Program::ClearData();
	ParseSource("simpleAssignmentTest.txt");
	ProgramTNode program = Program::GetASTRootNode();
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
	Program::ClearData();
	ParseSource("additionTest.txt");
	ProgramTNode program = Program::GetASTRootNode();
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
	Program::ClearData();
	ParseSource("whileTest.txt");
	ProgramTNode program = Program::GetASTRootNode();
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
	Program::ClearData();
	ParseSource("nestedWhileTest.txt");
	ProgramTNode program = Program::GetASTRootNode();
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

void ParserTest::TestParsing() {
	Program::ClearData();
	ParseSource("sample_SIMPLE_source.txt");
	ProgramTNode program = Program::GetASTRootNode();
	ProcedureTNode procedure = program.GetChild(0);
	vector<StmtTNode*> stmts = procedure.GetProcedureBody().GetStmtList();

	// procedure ABC {
	CPPUNIT_ASSERT(procedure.GetProcName() == "ABC");

	//  i=1;
	CPPUNIT_ASSERT(stmts[0]->GetLineNumber() == 1);
	CPPUNIT_ASSERT(stmts[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmts[0]).GetContent() == "i");
	CPPUNIT_ASSERT(GetRHS(*stmts[0]).GetContent() == "1");

	// b=200 ;
	CPPUNIT_ASSERT(stmts[1]->GetLineNumber() == 2);
	CPPUNIT_ASSERT(stmts[1]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmts[1]).GetContent() == "b");
	CPPUNIT_ASSERT(GetRHS(*stmts[1]).GetContent() == "200");

	// 	c= a   ;
	CPPUNIT_ASSERT(stmts[2]->GetLineNumber() == 3);
	CPPUNIT_ASSERT(stmts[2]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmts[2]).GetContent() == "c");
	CPPUNIT_ASSERT(GetRHS(*stmts[2]).GetContent() == "a");

	// while a	
	CPPUNIT_ASSERT(stmts[3]->GetLineNumber() == 4);
	CPPUNIT_ASSERT(stmts[3]->GetType() == TNode::WHILE);
	WhileTNode stmt4 = *dynamic_cast<WhileTNode*>(stmts[3]);
	vector<StmtTNode*> stmtList4 = stmt4.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt4.GetCondition().GetContent() == "a");

	//    while beta {
	CPPUNIT_ASSERT(stmtList4[0]->GetLineNumber() == 5);
	CPPUNIT_ASSERT(stmtList4[0]->GetType() == TNode::WHILE);
	WhileTNode stmt5 = *dynamic_cast<WhileTNode*>(stmtList4[0]);
	vector<StmtTNode*> stmtList5 = stmt5.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt5.GetCondition().GetContent() == "beta");

	//         oSCar  = 1 + beta + tmp;
	CPPUNIT_ASSERT(stmtList5[0]->GetLineNumber() == 6);
	CPPUNIT_ASSERT(stmtList5[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList5[0]).GetContent() == "oSCar");
	CPPUNIT_ASSERT(GetRHS(*stmtList5[0]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList5[0])).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList5[0])).GetContent() == "tmp");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetRHS(*stmtList5[0]))).GetContent() == "1");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetRHS(*stmtList5[0]))).GetContent() == "beta");

	//         while tmp{
	CPPUNIT_ASSERT(stmtList5[1]->GetLineNumber() == 7);
	CPPUNIT_ASSERT(stmtList5[1]->GetType() == TNode::WHILE);
	WhileTNode stmt7 = *dynamic_cast<WhileTNode*>(stmtList5[1]);
	vector<StmtTNode*> stmtList7 = stmt7.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt7.GetCondition().GetContent() == "tmp");

	//           oSCar = I + k + j1k + chArlie; }
	CPPUNIT_ASSERT(stmtList7[0]->GetLineNumber() == 8);
	CPPUNIT_ASSERT(stmtList7[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList7[0]).GetContent() == "oSCar");
	CPPUNIT_ASSERT(GetRHS(*stmtList7[0]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList7[0])).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList7[0])).GetContent() == "chArlie");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetRHS(*stmtList7[0]))).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetRHS(*stmtList7[0]))).GetContent() == "j1k");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetLHS(GetRHS(*stmtList7[0])))).GetContent() == "I");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetLHS(GetRHS(*stmtList7[0])))).GetContent() == "k");

	// 	while x 
	CPPUNIT_ASSERT(stmtList5[2]->GetLineNumber() == 9);
	CPPUNIT_ASSERT(stmtList5[2]->GetType() == TNode::WHILE);
	WhileTNode stmt9 = *dynamic_cast<WhileTNode*>(stmtList5[2]);
	vector<StmtTNode*> stmtList9 = stmt9.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt9.GetCondition().GetContent() == "x");

	//         x = x + 1;
	CPPUNIT_ASSERT(stmtList9[0]->GetLineNumber() == 10);
	CPPUNIT_ASSERT(stmtList9[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList9[0]).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(*stmtList9[0]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList9[0])).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList9[0])).GetContent() == "1");

	//        while left {
	CPPUNIT_ASSERT(stmtList9[1]->GetLineNumber() == 11);
	CPPUNIT_ASSERT(stmtList9[1]->GetType() == TNode::WHILE);
	WhileTNode stmt11 = *dynamic_cast<WhileTNode*>(stmtList9[1]);
	vector<StmtTNode*> stmtList11 = stmt11.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt11.GetCondition().GetContent() == "left");

	//           while right {
	CPPUNIT_ASSERT(stmtList11[0]->GetLineNumber() == 12);
	CPPUNIT_ASSERT(stmtList11[0]->GetType() == TNode::WHILE);
	WhileTNode stmt12 = *dynamic_cast<WhileTNode*>(stmtList11[0]);
	vector<StmtTNode*> stmtList12 = stmt12.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt12.GetCondition().GetContent() == "right");

	//             Romeo = Romeo + 1;
	CPPUNIT_ASSERT(stmtList12[0]->GetLineNumber() == 13);
	CPPUNIT_ASSERT(stmtList12[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList12[0]).GetContent() == "Romeo");
	CPPUNIT_ASSERT(GetRHS(*stmtList12[0]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList12[0])).GetContent() == "Romeo");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList12[0])).GetContent() == "1");

	//             b = 0;
	CPPUNIT_ASSERT(stmtList12[1]->GetLineNumber() == 14);
	CPPUNIT_ASSERT(stmtList12[1]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList12[1]).GetContent() == "b");
	CPPUNIT_ASSERT(GetRHS(*stmtList12[1]).GetContent() == "0");

	//             c = delta    + l  + width + Romeo ; }
	CPPUNIT_ASSERT(stmtList12[2]->GetLineNumber() == 15);
	CPPUNIT_ASSERT(stmtList12[2]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList12[2]).GetContent() == "c");
	CPPUNIT_ASSERT(GetRHS(*stmtList12[2]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList12[2])).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList12[2])).GetContent() == "Romeo");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetRHS(*stmtList12[2]))).GetContent() == "+");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetRHS(*stmtList12[2]))).GetContent() == "width");
	CPPUNIT_ASSERT(GetLHS(GetLHS(GetLHS(GetRHS(*stmtList12[2])))).GetContent() == "delta");
	CPPUNIT_ASSERT(GetRHS(GetLHS(GetLHS(GetRHS(*stmtList12[2])))).GetContent() == "l");

	//             while c {
	CPPUNIT_ASSERT(stmtList11[1]->GetLineNumber() == 16);
	CPPUNIT_ASSERT(stmtList11[1]->GetType() == TNode::WHILE);
	WhileTNode stmt16 = *dynamic_cast<WhileTNode*>(stmtList11[1]);
	vector<StmtTNode*> stmtList16 = stmt16.GetBody().GetStmtList();
	CPPUNIT_ASSERT(stmt16.GetCondition().GetContent() == "c");

	//               c = c +1   	; }
	CPPUNIT_ASSERT(stmtList16[0]->GetLineNumber() == 17);
	CPPUNIT_ASSERT(stmtList16[0]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList16[0]).GetContent() == "c");
	CPPUNIT_ASSERT(GetRHS(*stmtList16[0]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList16[0])).GetContent() == "c");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList16[0])).GetContent() == "1");

	//             x = x+ 1	; }}
	CPPUNIT_ASSERT(stmtList11[2]->GetLineNumber() == 18);
	CPPUNIT_ASSERT(stmtList11[2]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList11[2]).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(*stmtList11[2]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList11[2])).GetContent() == "x");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList11[2])).GetContent() == "1");

	//           a=   2; }
	CPPUNIT_ASSERT(stmtList5[3]->GetLineNumber() == 19);
	CPPUNIT_ASSERT(stmtList5[3]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList5[3]).GetContent() == "a");
	CPPUNIT_ASSERT(GetRHS(*stmtList5[3]).GetContent() == "2");

	//    w = w+1  ;
	CPPUNIT_ASSERT(stmtList4[1]->GetLineNumber() == 20);
	CPPUNIT_ASSERT(stmtList4[1]->GetContent() == "=");
	CPPUNIT_ASSERT(GetLHS(*stmtList4[1]).GetContent() == "w");
	CPPUNIT_ASSERT(GetRHS(*stmtList4[1]).GetContent() == "+");
	CPPUNIT_ASSERT(GetLHS(GetRHS(*stmtList4[1])).GetContent() == "w");
	CPPUNIT_ASSERT(GetRHS(GetRHS(*stmtList4[1])).GetContent() == "1");

}