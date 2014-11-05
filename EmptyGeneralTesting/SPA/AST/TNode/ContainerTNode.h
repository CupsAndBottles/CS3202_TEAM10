#pragma once

#include "TNode.h"

class ContainerTNode :
	public TNode {
public:
	virtual ContainerTNode* getRightSibling();

	string getContent();

protected:
	ContainerTNode(Type);

};

