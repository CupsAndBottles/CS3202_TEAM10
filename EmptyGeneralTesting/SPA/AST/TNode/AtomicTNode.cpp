#include "AtomicTNode.h"

AtomicTNode::AtomicTNode(TNode* directParent, TNode* rightSibling, Type type, string content)
	: TNode(directParent, rightSibling, type, content) {
}

vector<TNode> AtomicTNode::getChildren() {
	throwUnsupportedOperationException();
	return TNode::getChildren();
}

void AtomicTNode::addChild() {
	throwUnsupportedOperationException();
}


