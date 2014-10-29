#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "BinaryTNode.h"
#include "VariableTNode.h"

class AssignmentTNode :
	public StmtTNode,
	public BinaryTNode {
public:
	VariableTNode& getLHS();
private:
	AssignmentTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, VariableTNode, TNode);
};

