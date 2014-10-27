#pragma once

#include "AST\TNode\ConditionalTNode.h"
#include "AST\TNode\StmtListTNode.h"

class WhileTNode :
	public ConditionalTNode {
public:
	StmtListTNode& getBody();
private:
	WhileTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, VariableTNode, StmtListTNode);
};

