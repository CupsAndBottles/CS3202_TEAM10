#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(string procName)
	: TNode(Procedure, procName) {

	buildName(enumToString(Procedure).append(":").append(procName));
}

void ProcedureTNode::setProcedureBody(StmtListTNode* body) {
	addChild(body);
}

StmtListTNode& ProcedureTNode::getProcedureBody() {
	return dynamic_cast<StmtListTNode&>(getChild(0));
}

string ProcedureTNode::getProcName() {
	return TNode::getContent();
}
