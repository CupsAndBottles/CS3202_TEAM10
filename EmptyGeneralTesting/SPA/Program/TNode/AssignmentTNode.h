#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "BinaryTNode.h"
#include "VariableTNode.h"

class AssignmentTNode :
	public StmtTNode,
	public BinaryTNode {
public:
	AssignmentTNode(unsigned int);

	void BuildAssignmentNode(VariableTNode*, TNode*);
	VariableTNode& GetLHS();
	string GetContent();

private:

};

