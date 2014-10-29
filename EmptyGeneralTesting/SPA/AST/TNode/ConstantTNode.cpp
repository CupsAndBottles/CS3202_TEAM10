#include "ConstantTNode.h"

#include <string>

ConstantTNode::ConstantTNode(BinaryTNode* parent, int value)
	: AtomicTNode(parent, Constant, to_string((_Longlong)value))
	, value(value) {
		buildName(enumToString(Constant).append(":"));
}

int ConstantTNode::getValue() {
	return value;
}
