#include "ProgramTNode.h"


ProgramTNode::ProgramTNode(deque<ProcedureTNode> body) 
	: ContainerTNode(nullptr, nullptr, TNode::Program, TNode::dequeCaster<ProcedureTNode, TNode>(body)) {
	children = TNode::dequeCaster<ProcedureTNode, TNode>(body);
}

deque<ProcedureTNode> ProgramTNode::getBody() {
	return TNode::dequeCaster<TNode, ProcedureTNode>(getTNodes());
}

TNode* ProgramTNode::getDirectParent() {
	throwUnsupportedOperationException;
}

ContainerTNode* ProgramTNode::getRightSibling() {
	throwUnsupportedOperationException;
}