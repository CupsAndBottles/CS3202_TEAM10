#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "VariableTNode.h"

class ConditionalTNode :
	public StmtTNode {
public:
	VariableTNode getCondition();
protected:
	ConditionalTNode(StmtListTNode*, StmtTNode*, Type, int, StmtTNode*, VariableTNode);
};

