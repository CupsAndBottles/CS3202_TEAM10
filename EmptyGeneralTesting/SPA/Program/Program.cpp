#pragma once

#include "Program.h"
#include "Parser\Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\IfTNode.h"
#include "TNode\WhileTNode.h"
#include "TNode\CallTNode.h"

Program::Program() 
	: CFGRoot(CFGNode(1)) {}

ProgramTNode& Program::getASTRootNode() {
	return program;
}

CFGNode& Program::getCFGRootNode() {
	return CFGRoot;
}

StmtTNode& Program::getStmtNumber(int stmtNum) {
	return *(stmtNumberMap[stmtNum]);
}

