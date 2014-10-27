#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(TNode* directParent, ContainerTNode* rightSibling, Type type, deque<TNode> nodes)
	: TNode(directParent, rightSibling, type) {
	children = nodes;
}

ContainerTNode* ContainerTNode::getRightSibling() {
	return typecast<TNode*, ContainerTNode*>(rightSibling);
}