#include "ProgramTNode.h"


ProgramTNode::ProgramTNode(string name, deque<ProcedureTNode> body) 
	: ContainerTNode(nullptr, nullptr, TNode::Program, TNode::dequeCaster<ProcedureTNode, TNode>(body)) {
	children = TNode::dequeCaster<ProcedureTNode, TNode>(body);
	name = (TNode::enumToString(TNode::Program) + ":" + name);
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