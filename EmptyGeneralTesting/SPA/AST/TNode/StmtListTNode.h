#pragma once

#include "ContainerTNode.h"
#include "StmtTNode.h"

class StmtListTNode :
	public ContainerTNode {
public:
	StmtListTNode(string);

	StmtTNode& getChild(int);
	void addChild(StmtTNode);
	vector<StmtTNode> getStmtList();

protected:

};

