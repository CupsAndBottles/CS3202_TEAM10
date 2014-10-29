#include "ProgramTNode.h"


ProgramTNode::ProgramTNode(vector<ProcedureTNode> body) 
	: ContainerTNode(nullptr, nullptr, Program, TNode::vectorCaster<ProcedureTNode, TNode>(body)) {
	children = TNode::vectorCaster<ProcedureTNode, TNode>(body);
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