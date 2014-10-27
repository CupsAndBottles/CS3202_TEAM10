#pragma once
#include "AST\TNode\AtomicTNode.h"

class VariableTNode :
	public AtomicTNode {
public:

protected:
	VariableTNode(TNode*, TNode*, string);
};

