#pragma once

#include "TNode.h"

#include <deque>

class ContainerTNode :
	public TNode {
public:
	deque<TNode> getTNodes();
	virtual ContainerTNode* getRightSibling();
protected:
	ContainerTNode(TNode*, ContainerTNode*, Type, deque<TNode>);
};

