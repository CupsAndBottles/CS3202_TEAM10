#include "StmtTNode.h"

StmtTNode::StmtTNode(TNode* directParent, StmtTNode* rightSibling, Type type, int lineNumber, StmtTNode* logicalParent)
	: TNode(directParent, rightSibling, type)
	, lineNumber(lineNumber) 
	, logicalParent(logicalParent) {
}

StmtTNode* StmtTNode::getParent() {
	return logicalParent;
}

StmtTNode* StmtTNode::getFollows() {
	return TNode::typecast<TNode*, StmtTNode*>(rightSibling);
}

int StmtTNode::getLineNumber() {
	return lineNumber;
}