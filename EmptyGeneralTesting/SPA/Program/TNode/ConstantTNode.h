#pragma once

#include "AtomicTNode.h"
#include "BinaryTNode.h"

class ConstantTNode :
	public AtomicTNode {
public:
	ConstantTNode(string);

	unsigned int GetValue();

protected:
	unsigned int value;

};

