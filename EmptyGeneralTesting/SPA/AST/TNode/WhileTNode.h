#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class WhileTNode :
	public ConditionalTNode {
public:
	WhileTNode(StmtListTNode*, int, StmtTNode*);

	StmtListTNode& getBody();
private:

};

