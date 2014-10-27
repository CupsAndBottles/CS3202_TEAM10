#pragma once

#include "AST/TNode/StmtTNode.h"
#include "AST/TNode/VariableTNode.h"

class ConditionalTNode :
	public StmtTNode {
public:
	VariableTNode getCondition();
protected:
	ConditionalTNode(StmtListTNode*, StmtTNode*, Type, int, StmtTNode*, VariableTNode);
};

