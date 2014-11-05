#pragma once

#include "Parser\Token.h"
#include "CFG\CFGNode.h"
#include "TNode\StmtTNode.h"
#include "TNode\ProgramTNode.h"

#include <map>

class Program {
public:
	Program();

	ProgramTNode& getASTRootNode();
	CFGNode& getCFGRootNode();
	StmtTNode& getStmtNumber(int);

private:
	ProgramTNode program;
	CFGNode CFGRoot;
	vector<StmtTNode*> stmtNumberMap;
};

