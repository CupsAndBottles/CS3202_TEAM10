#include "BinaryTNode.h"

BinaryTNode::BinaryTNode(string opr)
	: TNode(BinaryOperator, opr) {
}

void BinaryTNode::buildBinaryNode(TNode LHS, TNode RHS) {
	addChild(LHS);
	addChild(RHS);
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


