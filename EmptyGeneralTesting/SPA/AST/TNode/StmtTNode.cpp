#include "StmtTNode.h"

StmtTNode::StmtTNode(Type type, int lineNumber)
	: TNode(type)
	, lineNumber(lineNumber) {
}

void StmtTNode::setParent(StmtTNode* logicalParent) {
	logicalParent = logicalParent;
}

StmtTNode* StmtTNode::getParent() {
	return logicalParent;
}

StmtTNode* StmtTNode::getFollows() {
	return TNode::typecast<StmtTNode*>(rightSibling);
}

int StmtTNode::getLineNumber() {
	return lineNumber;
}