#include "AssignmentTNode.h"

AssignmentTNode::AssignmentTNode(StmtListTNode* directParent, int lineNumber, StmtTNode* logicalParent)
	: TNode(directParent, Assignment, "=")
	, StmtTNode(directParent, Assignment, lineNumber, logicalParent)
	, BinaryTNode(directParent, "=") {

	buildName(enumToString(Assignment));
}

VariableTNode& AssignmentTNode::getLHS() {
	return typecast<TNode, VariableTNode>(getChild(0));
}
