#include "ConstantTNode.h"

#include <string>

ConstantTNode::ConstantTNode(BinaryTNode* parent, TNode* rightSibling, int value)
	: AtomicTNode(parent, rightSibling, Constant, to_string((_Longlong)value))
	, value(value) {
		buildName(enumToString(Constant).append(":"));
}

int ConstantTNode::getValue() {
	return value;
}
