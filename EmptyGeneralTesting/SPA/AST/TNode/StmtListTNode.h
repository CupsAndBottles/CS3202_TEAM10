#pragma once

#include "ContainerTNode.h"
#include "StmtTNode.h"

class StmtListTNode :
	public ContainerTNode {
public:
	StmtListTNode(TNode*, string);

	vector<StmtTNode> getStmtList();

protected:

};

