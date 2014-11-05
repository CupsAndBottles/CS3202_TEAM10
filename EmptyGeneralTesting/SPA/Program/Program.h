#pragma once

#include "Parser\Token.h"
#include "TNode\StmtTNode.h"
#include "TNode\ProgramTNode.h"

#include <map>

class Program {
public:
	Program();

	ProgramTNode& GetASTRootNode();
	StmtTNode& GetStmtFromNumber(int);
	void InsertStmt(StmtTNode*);

private:
	ProgramTNode program;
	vector<StmtTNode*> stmtNumberMap;
};

