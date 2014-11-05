#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "VariableTNode.h"

class ConditionalTNode :
	public StmtTNode {
public:
	VariableTNode getCondition();

protected:
	ConditionalTNode(Type, int);

	void setCondition(VariableTNode*);

};

