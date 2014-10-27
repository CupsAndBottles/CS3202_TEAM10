#pragma once

#include "AtomicTNode.h"

AtomicTNode::AtomicTNode(TNode* directParent, TNode* rightSibling, Type type, string content)
	: TNode(directParent, rightSibling, type, content) {
}

const deque<TNode> AtomicTNode::getChildren() const {
	throwUnsupportedOperationException;
}

void AtomicTNode::addChild() const {
	throwUnsupportedOperationException;
}


