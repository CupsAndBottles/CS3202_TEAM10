#pragma once

#include "TNode.h"

class ContainerTNode :
	public TNode {
public:
	ContainerTNode(TNode*, Type);

	vector<TNode> getTNodes();
	virtual ContainerTNode* getRightSibling();

protected:

};

