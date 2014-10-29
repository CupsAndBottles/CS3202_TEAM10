#pragma once

#include "TNode.h"

class AtomicTNode :
	public TNode {
public:
	AtomicTNode(TNode*, Type, string);

	vector<TNode> getChildren();
	void addChild();

protected:

};

