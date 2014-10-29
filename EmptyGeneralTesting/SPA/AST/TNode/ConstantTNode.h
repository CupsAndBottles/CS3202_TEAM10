#pragma once

#include "AtomicTNode.h"
#include "BinaryTNode.h"

class ConstantTNode :
	public AtomicTNode {
public:
	ConstantTNode(BinaryTNode*, int);

	int getValue();

protected:
	int value;

};

