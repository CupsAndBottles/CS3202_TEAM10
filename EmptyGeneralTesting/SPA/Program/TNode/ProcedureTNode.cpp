#include "ProcedureTNode.h"

ProcedureTNode::ProcedureTNode(string procName)
	: TNode(PROCEDURE, procName) {

	BuildName(EnumToString(PROCEDURE).append(":").append(procName));
}

void ProcedureTNode::SetProcedureBody(StmtListTNode* body) {
	AddChild(body);
}

StmtListTNode& ProcedureTNode::GetProcedureBody() {
	return dynamic_cast<StmtListTNode&>(GetChild(0));
}

string ProcedureTNode::GetProcName() {
	return TNode::GetContent();
}
