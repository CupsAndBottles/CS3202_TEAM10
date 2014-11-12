#pragma once

#include "PKB\Token.h"
#include "TNode\StmtTNode.h"
#include "TNode\ProgramTNode.h"

#include <map>

class Program {
public:
	friend class Parser;
	static ProgramTNode& GetASTRootNode();
	static StmtTNode& GetStmtFromNumber(int);
	static void ClearData();

protected:
	static void InsertStmt(StmtTNode*);

private:
	Program();

	static ProgramTNode program;
	static vector<StmtTNode*> stmtNumberMap;
};

