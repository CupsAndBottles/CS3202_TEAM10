#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "VariableTNode.h"

class ConditionalTNode :
	public StmtTNode {
public:
	ConditionalTNode(StmtListTNode*, Type, int, StmtTNode*);

	VariableTNode getCondition();

protected:

};

