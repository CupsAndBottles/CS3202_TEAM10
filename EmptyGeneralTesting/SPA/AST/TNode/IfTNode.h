#pragma once

#include "AST\TNode\ConditionalTNode.h"
#include "AST\TNode\StmtListTNode.h"

class IfTNode :
	public ConditionalTNode {
public:
	StmtListTNode& getThenBody();
	StmtListTNode& getElseBody();
private:
	IfTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, VariableTNode, StmtListTNode, StmtListTNode);
};

