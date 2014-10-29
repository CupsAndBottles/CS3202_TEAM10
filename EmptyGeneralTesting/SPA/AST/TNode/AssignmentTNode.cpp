#include "AssignmentTNode.h"

AssignmentTNode::AssignmentTNode(int lineNumber)
	: TNode(Assignment, "=")
	, StmtTNode(Assignment, lineNumber)
	, BinaryTNode("=") {

	buildName(enumToString(Assignment));
}

void AssignmentTNode::buildAssignmentNode(VariableTNode LHS, TNode RHS) {
	buildBinaryNode(LHS, RHS);
}

VariableTNode& AssignmentTNode::getLHS() {
	return typecast<VariableTNode>(getChild(0));
}
