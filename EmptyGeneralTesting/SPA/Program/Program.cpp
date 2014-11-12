#pragma once

#include "Program.h"
#include "PKB\Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\WhileTNode.h"

ProgramTNode Program::program;
map<int, StmtTNode*> Program::stmtNumberMap;

Program::Program() {}

ProgramTNode& Program::GetASTRootNode() {
	return program;
}

StmtTNode& Program::GetStmtFromNumber(int stmtNum) {
	return *(stmtNumberMap[stmtNum]);
}

void Program::InsertStmt(StmtTNode* stmt, int stmtNum) {
	stmtNumberMap[stmtNum] = stmt;
}

void Program::ClearData() { // leaky method
	program = ProgramTNode();
	stmtNumberMap.clear();
}

