#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(Type type)
	: TNode(type) {
}

ContainerTNode* ContainerTNode::getRightSibling() {
	return typecast<ContainerTNode*>(rightSibling);
}