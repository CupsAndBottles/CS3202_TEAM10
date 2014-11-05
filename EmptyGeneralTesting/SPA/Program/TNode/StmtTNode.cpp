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
	return dynamic_cast<StmtTNode*>(rightSibling);
}

int StmtTNode::getLineNumber() {
	return lineNumber;
}

string StmtTNode::getContent() {
	throwUnsupportedOperationException();
	return TNode::getContent();
}