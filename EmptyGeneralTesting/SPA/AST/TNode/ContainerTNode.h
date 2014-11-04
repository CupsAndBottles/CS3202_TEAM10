#pragma once

#include "TNode.h"

class ContainerTNode :
	public TNode {
public:
	virtual ContainerTNode* getRightSibling();

protected:
	ContainerTNode(Type);

};

