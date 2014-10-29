#include "VariableTNode.h"

VariableTNode::VariableTNode(TNode* parent, string identifier)
	: AtomicTNode(parent, Variable, identifier) {
		buildName(enumToString(Variable).append(":"));
}
