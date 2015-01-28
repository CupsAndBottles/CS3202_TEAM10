#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"
#include "VariableTNode.h"

class ConditionalTNode :
	public StmtTNode {
public:
	VariableTNode GetCondition();

protected:
	ConditionalTNode(Type, unsigned int);

	void SetCondition(VariableTNode*);

};

