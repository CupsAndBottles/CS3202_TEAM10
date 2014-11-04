#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(string procName)
	: TNode(Procedure, procName) {

	buildName(enumToString(Procedure).append(":"));
}

void ProcedureTNode::setProcedureBody(StmtListTNode body) {
	addChild(body);
}

StmtListTNode& ProcedureTNode::getProcedureBody() {
	return dynamic_cast<StmtListTNode&>(getChild(0));
}

string ProcedureTNode::getContent() {
	return content;
}

string ProcedureTNode::getProcName() {
	return getContent();
}
