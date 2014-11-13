#pragma once

#include "AtomicTNode.h"
#include "BinaryTNode.h"

class ConstantTNode :
	public AtomicTNode {
public:
	ConstantTNode(string);

	int GetValue();

protected:
	int value;

};

