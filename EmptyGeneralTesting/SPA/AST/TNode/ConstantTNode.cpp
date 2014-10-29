#include "ConstantTNode.h"

#include <string>

ConstantTNode::ConstantTNode(string value)
	: AtomicTNode(Constant, value)
	, value(stoi(value)) {
		buildName(enumToString(Constant).append(":"));
}

int ConstantTNode::getValue() {
	return value;
}
