#pragma once

#include "TNode.h"

class AtomicTNode :
	public TNode {
public:
	const deque<TNode> getChildren() const;
	void addChild() const;
protected:
	AtomicTNode(TNode*, TNode*, Type, string);
};

