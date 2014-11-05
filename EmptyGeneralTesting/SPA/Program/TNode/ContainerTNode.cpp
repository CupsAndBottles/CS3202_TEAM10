#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(Type type)
	: TNode(type) {
}

ContainerTNode* ContainerTNode::GetRightSibling() {
	return dynamic_cast<ContainerTNode*>(rightSibling);
}

string ContainerTNode::GetContent() {
	ThrowUnsupportedOperationException();
	return TNode::GetContent();
}