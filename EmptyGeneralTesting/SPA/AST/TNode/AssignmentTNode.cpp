#include "AssignmentTNode.h"

AssignmentTNode::AssignmentTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, VariableTNode LHS, TNode RHS)
	: TNode(directParent, rightSibling, Assignment)
	, StmtTNode(directParent, rightSibling, Assignment, lineNumber, logicalParent)
	, BinaryTNode(directParent, rightSibling, Assignment, LHS, RHS) {

	buildName(enumToString(Assignment));
}

VariableTNode& AssignmentTNode::getLHS() {
	return typecast<TNode, VariableTNode>(getChild(0));
}
