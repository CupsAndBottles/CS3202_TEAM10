#pragma once

#include "Program.h"
#include "Parser\Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\IfTNode.h"
#include "TNode\WhileTNode.h"
#include "TNode\CallTNode.h"

Program::Program() {}

ProgramTNode& Program::GetASTRootNode() {
	return program;
}

StmtTNode& Program::GetStmtFromNumber(int stmtNum) {
	return *(stmtNumberMap[stmtNum]);
}

void Program::InsertStmt(StmtTNode* stmt) {
	stmtNumberMap.push_back(stmt);
}

