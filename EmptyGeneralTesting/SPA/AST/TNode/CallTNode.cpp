#include "CallTNode.h"

CallTNode::CallTNode(int lineNumber, string procName) 
	: TNode(Call, procName) 
	, StmtTNode(Call, lineNumber) {

	buildName(enumToString(Call).append(":"));
}

string CallTNode::getProcName(){
	return content;
}

string CallTNode::getContent() {
	return content;
}