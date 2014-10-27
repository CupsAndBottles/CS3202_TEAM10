#pragma once

#include "AST\TNode\StmtTNode.h"
#include "AST\TNode\BinaryTNode.h"
#include "AST\TNode\VariableTNode.h"

class AssignmentTNode :
	public StmtTNode,
	public BinaryTNode {
public:
	VariableTNode& getLHS();
private:
	AssignmentTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, VariableTNode, TNode);
};

