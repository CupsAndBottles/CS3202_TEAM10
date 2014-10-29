#include "ProgramTNode.h"


ProgramTNode::ProgramTNode(vector<ProcedureTNode> body) 
	: ContainerTNode(nullptr, Program) {
	setRightSibling(nullptr);
}

vector<ProcedureTNode> ProgramTNode::getBody() {
	return TNode::vectorCaster<TNode, ProcedureTNode>(getTNodes());
}

TNode* ProgramTNode::getDirectParent() {
	throwUnsupportedOperationException();
	return ContainerTNode::getDirectParent();
}

ContainerTNode* ProgramTNode::getRightSibling() {
	throwUnsupportedOperationException();
	return ContainerTNode::getRightSibling();
}