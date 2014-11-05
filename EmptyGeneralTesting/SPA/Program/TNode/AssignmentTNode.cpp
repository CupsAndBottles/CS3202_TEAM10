#include "AssignmentTNode.h"

AssignmentTNode::AssignmentTNode(int lineNumber)
	: TNode(ASSIGNMENT, "=")
	, StmtTNode(ASSIGNMENT, lineNumber)
	, BinaryTNode("=") {

	BuildName(EnumToString(ASSIGNMENT));
}

void AssignmentTNode::BuildAssignmentNode(VariableTNode* LHS, TNode* RHS) {
	BuildBinaryNode(LHS, RHS);
}

VariableTNode& AssignmentTNode::GetLHS() {
	return dynamic_cast<VariableTNode&>(GetChild(0));
}

string AssignmentTNode::GetContent() {
	return TNode::GetContent();
}