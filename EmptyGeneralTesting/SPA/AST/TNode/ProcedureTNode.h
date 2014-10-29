#pragma once

#include "StmtListTNode.h"

class ProcedureTNode :
	public TNode {
public:
	StmtListTNode& getProcedureBody();
	string getProcName();
	string getContent();
private:
	ProcedureTNode(TNode*, ProcedureTNode*, string, StmtListTNode);
};

