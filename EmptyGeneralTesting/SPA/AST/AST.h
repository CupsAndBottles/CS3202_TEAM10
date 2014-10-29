#pragma once

#include "Token.h"
#include "AST\TNode\StmtTNode.h"
#include "AST\TNode\ProgramTNode.h"

class AST {
public:
	AST();

	void InitNewProgram(ProgramTNode);
	StmtTNode& getStmtNumber(int);

private:
	vector<ProgramTNode> programs;
};

