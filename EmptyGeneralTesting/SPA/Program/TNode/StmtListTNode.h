#pragma once

#include "ContainerTNode.h"
#include "StmtTNode.h"

class StmtListTNode :
	public ContainerTNode {
public:
	StmtListTNode(string);

	StmtTNode& GetChild(unsigned int);
	void AddChild(StmtTNode*);
	vector<StmtTNode*> GetStmtList();
	string GetContent();

protected:

};

