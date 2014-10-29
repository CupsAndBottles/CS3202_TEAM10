#include "CallTNode.h"

CallTNode::CallTNode(StmtListTNode* directParent, int lineNumber, StmtTNode* logicalParent, string procName) 
	: TNode(directParent, Call, procName) 
	, StmtTNode(directParent, Call, lineNumber, logicalParent) {

	buildName(enumToString(Call).append(":"));
}

string CallTNode::getProcName(){
	return content;
}

string CallTNode::getContent() {
	return content;
}