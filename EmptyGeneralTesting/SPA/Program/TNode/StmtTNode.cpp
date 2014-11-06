#include "StmtTNode.h"

StmtTNode::StmtTNode(Type type, int lineNumber)
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

int StmtTNode::GetLineNumber() {
	return lineNumber;
}

string StmtTNode::GetContent() {
	ThrowUnsupportedOperationException();
	return TNode::GetContent();
}