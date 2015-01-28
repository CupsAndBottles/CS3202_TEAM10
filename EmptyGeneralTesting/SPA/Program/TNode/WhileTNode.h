#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class WhileTNode :
	public ConditionalTNode {
public:
	WhileTNode(unsigned int);

	void BuildWhileNode(VariableTNode*, StmtListTNode*);

	StmtListTNode& GetBody();
private:

};

