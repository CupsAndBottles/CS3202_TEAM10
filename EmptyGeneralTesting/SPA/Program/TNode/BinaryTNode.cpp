#include "BinaryTNode.h"

BinaryTNode::BinaryTNode(string opr)
	: TNode(BINARY_OPERATOR, opr) {
}

void BinaryTNode::BuildBinaryNode(TNode* LHS, TNode* RHS) {
	AddChild(LHS);
	AddChild(RHS);
}

TNode& BinaryTNode::GetLHS() {
	return GetChild(0);
}

TNode& BinaryTNode::GetRHS() {
	return GetChild(1);
}

string BinaryTNode::GetOperator() {
	return GetContent();
}


