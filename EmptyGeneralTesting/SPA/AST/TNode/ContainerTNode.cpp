#include "ContainerTNode.h"

ContainerTNode::ContainerTNode(Type type)
	: TNode(type) {
}

ContainerTNode* ContainerTNode::getRightSibling() {
	return dynamic_cast<ContainerTNode*>(rightSibling);
}