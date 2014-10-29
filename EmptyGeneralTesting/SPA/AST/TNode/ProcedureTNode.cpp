#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(TNode* directParent, ProcedureTNode* rightSibling, string procName, StmtListTNode body)
	: TNode(directParent, rightSibling, Procedure, procName) {

	addChild(body);
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
