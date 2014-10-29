#include "CallTNode.h"

CallTNode::CallTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, string procName) 
	: TNode(directParent, rightSibling, Call, procName) 
	, StmtTNode(directParent, rightSibling, Call, lineNumber, logicalParent) {

	buildName(enumToString(Call).append(":"));
}

string CallTNode::getProcName(){
	return content;
}

string CallTNode::getContent() {
	return content;
}