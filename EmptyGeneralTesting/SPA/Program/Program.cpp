#pragma once

#include "Program.h"
#include "..\Parser\Token.h"

Program::Program() {}

TNode Program::program = TNode::ConstructProgramTNode("");
map<unsigned int, TNode*> Program::stmtNumberMap = map<unsigned int, TNode*>();

TNode& Program::GetASTRootNode() {
	return program;
}

TNode& Program::GetStmtFromNumber(unsigned int stmtNum) {
	return *(stmtNumberMap[stmtNum]);
}

void Program::InsertStmt(TNode* stmt, unsigned int stmtNum) {
	stmtNumberMap[stmtNum] = stmt;
}

void Program::ClearData() { // leaky method
	Program::program = TNode::ConstructProgramTNode("");
	Program::stmtNumberMap = map<unsigned int, TNode*>();
}