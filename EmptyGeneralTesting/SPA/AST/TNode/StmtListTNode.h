#pragma once

#include "ContainerTNode.h"
#include "StmtTNode.h"

class StmtListTNode :
	public ContainerTNode {
public:
	StmtListTNode(string);

	void addChild(StmtTNode);
	vector<StmtTNode> getStmtList();

protected:

};

