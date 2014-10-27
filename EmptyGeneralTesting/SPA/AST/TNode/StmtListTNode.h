#pragma once

#include "AST\TNode\ContainerTNode.h"
#include "AST\TNode\StmtTNode.h"

#include <deque>

class StmtListTNode :
	public ContainerTNode {
public:
	deque<StmtTNode> getStmtList();
protected:
	StmtListTNode(string, deque<StmtTNode>, TNode*, StmtListTNode*);

};

