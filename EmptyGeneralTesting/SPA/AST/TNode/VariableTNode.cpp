#include "VariableTNode.h"

VariableTNode::VariableTNode(TNode* parent, TNode* rightSibling, string identifier)
	: AtomicTNode(parent, rightSibling, Variable, identifier) {
		buildName(enumToString(Variable).append(":"));
}
