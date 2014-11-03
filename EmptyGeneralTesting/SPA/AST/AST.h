#pragma once

#include "Token.h"
#include "AST\TNode\StmtTNode.h"
#include "AST\TNode\ProgramTNode.h"

class AST {
public:
	AST();

	ProgramTNode& getRootNode();
	StmtTNode& getStmtNumber(int);

private:
	ProgramTNode program;
};

