#include "AtomicTNode.h"

AtomicTNode::AtomicTNode(Type type, string content)
	: TNode(type, content) {
}

vector<TNode*> AtomicTNode::GetChildren() {
	// ThrowUnsupportedOperationException();
	return TNode::GetChildren();
}

void AtomicTNode::AddChild(TNode* child) {
	ThrowUnsupportedOperationException();
}


