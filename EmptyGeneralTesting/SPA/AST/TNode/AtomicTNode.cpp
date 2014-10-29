#include "AtomicTNode.h"

AtomicTNode::AtomicTNode(Type type, string content)
	: TNode(type, content) {
}

vector<TNode> AtomicTNode::getChildren() {
	throwUnsupportedOperationException();
	return TNode::getChildren();
}

void AtomicTNode::addChild() {
	throwUnsupportedOperationException();
}


