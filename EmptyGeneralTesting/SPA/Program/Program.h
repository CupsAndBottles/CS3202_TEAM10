#pragma once

#include "Parser\Token.h"
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
	static void InsertStmt(StmtTNode*, int);

private:
	Program();

	static ProgramTNode program;
	static map<int, StmtTNode*> stmtNumberMap;
};

