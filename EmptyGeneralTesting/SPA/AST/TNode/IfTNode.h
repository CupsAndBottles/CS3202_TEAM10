#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class IfTNode :
	public ConditionalTNode {
public:
	IfTNode(StmtListTNode*, int, StmtTNode*);

	StmtListTNode& getThenBody();
	StmtListTNode& getElseBody();

private:

};

