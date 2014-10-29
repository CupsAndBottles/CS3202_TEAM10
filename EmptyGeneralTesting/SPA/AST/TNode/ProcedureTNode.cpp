#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(TNode* directParent, string procName)
	: TNode(directParent, Procedure, procName) {

	buildName(enumToString(Procedure).append(":"));
}

StmtListTNode& ProcedureTNode::getProcedureBody() {
	return TNode::typecast<TNode, StmtListTNode>(getChild(0));
}

string ProcedureTNode::getContent() {
	return content;
}

string ProcedureTNode::getProcName() {
	return getContent();
}
