#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class WhileTNode :
	public ConditionalTNode {
public:
	StmtListTNode& getBody();
private:
	WhileTNode(StmtListTNode*, StmtTNode*, int, StmtTNode*, VariableTNode, StmtListTNode);
};

