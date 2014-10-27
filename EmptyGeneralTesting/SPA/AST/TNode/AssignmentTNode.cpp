#include "AssignmentTNode.h"

AssignmentTNode::AssignmentTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, VariableTNode LHS, TNode RHS)
	: TNode(directParent, rightSibling, TNode::Assignment)
	, StmtTNode(directParent, rightSibling, TNode::Assignment, lineNumber, logicalParent)
	, BinaryTNode(directParent, rightSibling, TNode::Assignment, LHS, RHS) {

	buildName(enumToString(TNode::Assignment));
}

VariableTNode& AssignmentTNode::getLHS() {
	return TNode::typecast<TNode, VariableTNode>(getChild(0));
}
