#include "CallTNode.h"


CallTNode::CallTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, string procName) 
	: TNode(directParent, rightSibling, TNode::Call, procName) 
	, StmtTNode(directParent, rightSibling, TNode::Call, lineNumber, logicalParent) {

	buildName(enumToString(TNode::Call) + ":");
}

string CallTNode::getProcName(){
	return content;
}

string CallTNode::getContent() {
	return content;
}