#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(TNode* directParent, ContainerTNode* rightSibling, Type type, vector<TNode> nodes)
	: TNode(directParent, rightSibling, type) {
	addChildren(nodes);
}

ContainerTNode* ContainerTNode::getRightSibling() {
	return typecast<TNode*, ContainerTNode*>(rightSibling);
}