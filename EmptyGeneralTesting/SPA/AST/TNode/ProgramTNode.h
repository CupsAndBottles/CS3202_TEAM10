#pragma once

#include "ContainerTNode.h"
#include "ProcedureTNode.h"

class ProgramTNode :
	public ContainerTNode {
public:
	ProgramTNode();

	vector<ProcedureTNode> getBody();
	TNode* getDirectParent();
	ContainerTNode* getRightSibling();
	void addChild(ProcedureTNode);

protected:

};

