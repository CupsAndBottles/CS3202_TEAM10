#include "ConstantTNode.h"

#include <string>

ConstantTNode::ConstantTNode(string value)
	: AtomicTNode(CONSTANT, value)
	, value(stoi(value)) {
		BuildName(EnumToString(CONSTANT).append(":"));
}

int ConstantTNode::GetValue() {
	return value;
}
