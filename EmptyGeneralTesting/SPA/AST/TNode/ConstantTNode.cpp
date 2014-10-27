#include "ConstantTNode.h"

#include <string>

using namespace std;

ConstantTNode::ConstantTNode(BinaryTNode* parent, TNode* rightSibling, int value)
	: AtomicTNode(parent, rightSibling, TNode::Constant, to_string(value))
	, value(value) {
	buildName(enumToString(TNode::Constant) + ":");
}

int ConstantTNode::getValue() {
	return value;
}
