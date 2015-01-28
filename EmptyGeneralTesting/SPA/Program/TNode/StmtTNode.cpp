#include "StmtTNode.h"

StmtTNode::StmtTNode(Type type, unsigned int lineNumber)
	: TNode(type)
	, lineNumber(lineNumber) {
}

void StmtTNode::SetParent(StmtTNode* logicalParent) {
	logicalParent = logicalParent;
}

StmtTNode* StmtTNode::GetParent() {
	return logicalParent;
}

StmtTNode* StmtTNode::GetFollows() {
	return dynamic_cast<StmtTNode*>(rightSibling);
}

unsigned int StmtTNode::GetLineNumber() {
	return lineNumber;
}

string StmtTNode::GetContent() {
	ThrowUnsupportedOperationException();
	return TNode::GetContent();
}