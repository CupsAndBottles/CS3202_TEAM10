#include "ProgramTNode.h"

ProgramTNode::ProgramTNode() 
	: ContainerTNode(Program) {
	directParent = nullptr;
	rightSibling = nullptr;
}

ProcedureTNode& ProgramTNode::getChild(int index) {
	return typecast<ProcedureTNode&>(TNode(getChild(index)));
}

vector<ProcedureTNode> ProgramTNode::getBody() {
	return TNode::vectorCaster<ProcedureTNode>(getTNodes());
}

TNode* ProgramTNode::getDirectParent() {
	throwUnsupportedOperationException();
	return ContainerTNode::getDirectParent();
}

ContainerTNode* ProgramTNode::getRightSibling() {
	throwUnsupportedOperationException();
	return ContainerTNode::getRightSibling();
}

void ProgramTNode::addChild(ProcedureTNode procedure) {
	TNode::addChild(procedure);
}