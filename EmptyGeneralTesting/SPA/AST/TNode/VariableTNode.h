#pragma once

#include "AtomicTNode.h"

class VariableTNode :
	public AtomicTNode {
public:

protected:
	VariableTNode(TNode*, TNode*, string);
};

