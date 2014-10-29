#pragma once

#include "TNode.h"

class BinaryTNode : 
	public virtual TNode {
public:
	virtual TNode& getLHS();
	TNode& getRHS();
protected:
	BinaryTNode(TNode*, TNode*, Type, TNode, TNode);
};

