#include "ProgramTNode.h"

ProgramTNode::ProgramTNode() 
	: ContainerTNode(Program) {
	directParent = nullptr;
	rightSibling = nullptr;
}

ProcedureTNode& ProgramTNode::getChild(int index) {
	return dynamic_cast<ProcedureTNode&>(TNode::getChild(index));
}

vector<ProcedureTNode*> ProgramTNode::getBody() {
	vector<ProcedureTNode*> result;
	for (unsigned int i = 0; i < children.size(); i++) {
		result.push_back(dynamic_cast<ProcedureTNode*>(children[i]));
	}

	return result;
}

TNode* ProgramTNode::getDirectParent() {
	throwUnsupportedOperationException();
	return ContainerTNode::getDirectParent();
}

ContainerTNode* ProgramTNode::getRightSibling() {
	throwUnsupportedOperationException();
	return ContainerTNode::getRightSibling();
}

void ProgramTNode::addChild(ProcedureTNode* procedure) {
	TNode::addChild(procedure);
}