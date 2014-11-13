#pragma once

#include "TNode.h"

class ContainerTNode :
	public TNode {
public:
	virtual ContainerTNode* GetRightSibling();

	string GetContent();

protected:
	ContainerTNode(Type);

};

