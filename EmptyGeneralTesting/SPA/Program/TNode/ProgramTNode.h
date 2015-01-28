#pragma once

#include "ContainerTNode.h"
#include "ProcedureTNode.h"

class ProgramTNode :
	public ContainerTNode {
public:
	ProgramTNode();

	ProcedureTNode& GetChild(unsigned int);
	vector<ProcedureTNode*> GetBody();
	TNode* GetDirectParent();
	ContainerTNode* GetRightSibling();
	void AddChild(ProcedureTNode*);

protected:

};

