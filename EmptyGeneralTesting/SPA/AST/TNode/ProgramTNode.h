#pragma once

#include "ContainerTNode.h"
#include "ProcedureTNode.h"

class ProgramTNode :
	public ContainerTNode {
public:
	vector<ProcedureTNode> getBody();
	TNode* getDirectParent();
	ContainerTNode* getRightSibling();
private:
	ProgramTNode(vector<ProcedureTNode>);
};

