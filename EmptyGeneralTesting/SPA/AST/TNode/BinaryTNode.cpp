#include "BinaryTNode.h"


BinaryTNode::BinaryTNode(TNode* parent, TNode* rightSibling, TNode::Type type, TNode LHS, TNode RHS)
	: TNode(parent, rightSibling, type) {
	addChild(LHS);
	addChild(RHS);
}

TNode& BinaryTNode::getLHS() {
	return getChild(0);
}

TNode& BinaryTNode::getRHS() {
	return getChild(1);
}


