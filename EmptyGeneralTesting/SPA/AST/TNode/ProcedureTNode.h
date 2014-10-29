#pragma once

#include "StmtListTNode.h"

class ProcedureTNode :
	public TNode {
public:
	ProcedureTNode(string);

	void setProcedureBody(StmtListTNode);
	StmtListTNode& getProcedureBody();
	string getProcName();
	string getContent();

private:

};

