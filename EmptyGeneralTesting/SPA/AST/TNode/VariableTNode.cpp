#include "VariableTNode.h"

VariableTNode::VariableTNode(TNode* parent, TNode* rightSibling, string identifier)
	: AtomicTNode(parent, rightSibling, TNode::Variable, identifier) {
	buildName(enumToString(TNode::Variable) + ":");
}
