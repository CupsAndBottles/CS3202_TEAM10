#pragma once

#include "AST\TNode\StmtListTNode.h"
#include "AST\TNode\ProgramTNode.h"

class ProcedureTNode :
	public TNode {
public:
	StmtListTNode& getProcedureBody();
	string getProcName();
	string getContent();
private:
	ProcedureTNode(ProgramTNode*, ProcedureTNode*, string, StmtListTNode);
};

