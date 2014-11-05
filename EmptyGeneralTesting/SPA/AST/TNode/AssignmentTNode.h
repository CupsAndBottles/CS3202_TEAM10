#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "BinaryTNode.h"
#include "VariableTNode.h"

class AssignmentTNode :
	public StmtTNode,
	public BinaryTNode {
public:
	AssignmentTNode(int);

	void buildAssignmentNode(VariableTNode*, TNode*);
	VariableTNode& getLHS();
	string getContent();

private:

};

