#include "VariableTNode.h"

VariableTNode::VariableTNode(string identifier)
	: AtomicTNode(Variable, identifier) {
		buildName(enumToString(Variable).append(":"));
}
