#pragma once

#include "TNode.h"

class AtomicTNode :
	public TNode {
public:
	vector<TNode> getChildren();
	void addChild();
protected:
	AtomicTNode(TNode*, TNode*, Type, string);
};

