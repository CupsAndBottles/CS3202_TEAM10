#include "AtomicTNode.h"

AtomicTNode::AtomicTNode(TNode* directParent, Type type, string content)
	: TNode(directParent, type, content) {
}

vector<TNode> AtomicTNode::getChildren() {
	throwUnsupportedOperationException();
	return TNode::getChildren();
}

void AtomicTNode::addChild() {
	throwUnsupportedOperationException();
}


