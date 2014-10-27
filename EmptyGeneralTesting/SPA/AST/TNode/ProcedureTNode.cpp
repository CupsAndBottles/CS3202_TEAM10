#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(ProgramTNode* directParent, ProcedureTNode* rightSibling, string procName, StmtListTNode body)
	: TNode(directParent, rightSibling, TNode::Procedure, procName) {

	addChild(body);
	buildName(enumToString(TNode::Procedure) + ":");
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
