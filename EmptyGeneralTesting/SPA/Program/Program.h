#pragma once

#include "PKB\Token.h"
#include "TNode\StmtTNode.h"
#include "TNode\ProgramTNode.h"

#include <map>

class Program {
public:
	static ProgramTNode& GetASTRootNode();
	static StmtTNode& GetStmtFromNumber(int);
	static void InsertStmt(StmtTNode*);
	static void ClearData();

private:
	Program();

	static ProgramTNode program;
	static vector<StmtTNode*> stmtNumberMap;
};

