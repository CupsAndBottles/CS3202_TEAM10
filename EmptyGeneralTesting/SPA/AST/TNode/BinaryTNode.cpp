#include "BinaryTNode.h"

BinaryTNode::BinaryTNode(TNode* parent, string opr)
	: TNode(parent, BinaryOperator, opr) {
}

TNode& BinaryTNode::getLHS() {
	return getChild(0);
}

TNode& BinaryTNode::getRHS() {
	return getChild(1);
}

string BinaryTNode::getContent() {
	return content;
}

string BinaryTNode::getOperator() {
	return getContent();
}


