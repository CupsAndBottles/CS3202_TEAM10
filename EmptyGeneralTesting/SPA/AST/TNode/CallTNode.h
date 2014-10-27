#pragma once

#include "AST\TNode\StmtTNode.h"

class CallTNode :
	public StmtTNode {
public:
	string getProcName();
	string getContent();
private:
	CallTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, string);
};

