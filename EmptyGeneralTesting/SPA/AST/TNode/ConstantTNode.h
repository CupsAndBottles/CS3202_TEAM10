#pragma once

#include "AST\TNode\AtomicTNode.h"
#include "AST\TNode\BinaryTNode.h"

class ConstantTNode :
	public AtomicTNode {
public:
	int getValue();
protected:
	ConstantTNode(BinaryTNode*, TNode*, int);
	int value;
};

