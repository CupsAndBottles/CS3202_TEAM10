#pragma once

#include "Program.h"
#include "..\Parser\Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\WhileTNode.h"

ProgramTNode Program::program;
map<unsigned int, StmtTNode*> Program::stmtNumberMap;

Program::Program() {}

ProgramTNode& Program::GetASTRootNode() {
	return program;
}

StmtTNode& Program::GetStmtFromNumber(unsigned int stmtNum) {
	return *(stmtNumberMap[stmtNum]);
}

void Program::InsertStmt(StmtTNode* stmt, unsigned int stmtNum) {
	stmtNumberMap[stmtNum] = stmt;
}

void Program::ClearData() { // leaky method
	program = ProgramTNode();
	stmtNumberMap.clear();
}

