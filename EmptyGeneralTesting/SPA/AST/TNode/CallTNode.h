#pragma once

#include "AST\TNode\StmtTNode.h"
#include "AST\TNode\StmtListTNode.h"

class CallTNode :
	public StmtTNode {
public:
	string getProcName();
	string getContent();
protected:
	CallTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, string);
};

