#pragma once

#include "..\Parser\Token.h"
#include "TNode\TNode.h"

#include <map>

class Program {
public:
	friend class Parser;
	static TNode& GetASTRootNode();
	static TNode& GetStmtFromNumber(unsigned int);
	static void ClearData();

protected:
	static void InsertStmt(TNode*, unsigned int);

private:
	Program();

	static TNode program;
	static map<unsigned int, TNode*> stmtNumberMap;
};

