#pragma once

#include "ContainerTNode.h"
#include "StmtTNode.h"

class StmtListTNode :
	public ContainerTNode {
public:
	vector<StmtTNode> getStmtList();
protected:
	StmtListTNode(TNode*, StmtListTNode*, string, vector<StmtTNode>);

};

