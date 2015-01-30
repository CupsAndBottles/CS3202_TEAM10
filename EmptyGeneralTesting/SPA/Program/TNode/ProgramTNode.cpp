#include "ProgramTNode.h"

ProgramTNode::ProgramTNode() 
	: ContainerTNode(PROGRAM) {
	directParent = nullptr;
	rightSibling = nullptr;
}

ProcedureTNode& ProgramTNode::GetChild(unsigned int index) {
	return dynamic_cast<ProcedureTNode&>(TNode::GetChild(index));
}

vector<ProcedureTNode*> ProgramTNode::GetBody() {
	vector<ProcedureTNode*> result;
	for (unsigned int i = 0; i < children.size(); i++) {
		result.push_back(dynamic_cast<ProcedureTNode*>(children[i]));
	}

	return result;
}

TNode* ProgramTNode::GetDirectParent() {
	ThrowUnsupportedOperationException();
	return ContainerTNode::GetDirectParent();
}

ContainerTNode* ProgramTNode::GetRightSibling() {
	ThrowUnsupportedOperationException();
	return ContainerTNode::GetRightSibling();
}

void ProgramTNode::AddChild(ProcedureTNode* procedure) {
	TNode::AddChild(procedure);
}