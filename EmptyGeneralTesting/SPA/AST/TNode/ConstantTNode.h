#pragma once

#include "AtomicTNode.h"
#include "BinaryTNode.h"

class ConstantTNode :
	public AtomicTNode {
public:
	ConstantTNode(string);

	int getValue();

protected:
	int value;

};

