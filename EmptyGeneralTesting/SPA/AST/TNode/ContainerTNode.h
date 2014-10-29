#pragma once

#include "TNode.h"

class ContainerTNode :
	public TNode {
public:
	vector<TNode> getTNodes();
	virtual ContainerTNode* getRightSibling();

protected:
	ContainerTNode(Type);

};

