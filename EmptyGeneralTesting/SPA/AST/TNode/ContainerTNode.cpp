#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(TNode* directParent, Type type)
	: TNode(directParent, type) {
}

ContainerTNode* ContainerTNode::getRightSibling() {
	return typecast<TNode*, ContainerTNode*>(rightSibling);
}