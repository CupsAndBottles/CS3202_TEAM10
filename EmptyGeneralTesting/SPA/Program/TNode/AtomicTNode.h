#pragma once

#include "TNode.h"

class AtomicTNode :
	public TNode {
public:
	vector<TNode*> GetChildren();
	void AddChild(TNode* child);

protected:
	AtomicTNode(Type, string);

};

