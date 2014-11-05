#pragma once

#include "TNode.h"

class AtomicTNode :
	public TNode {
public:
	vector<TNode*> getChildren();
	void addChild(TNode* child);

protected:
	AtomicTNode(Type, string);

};

