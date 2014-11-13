#pragma once

#include "StmtListTNode.h"

class ProcedureTNode :
	public TNode {
public:
	ProcedureTNode(string);

	void SetProcedureBody(StmtListTNode*);
	StmtListTNode& GetProcedureBody();
	string GetProcName();

private:

};

