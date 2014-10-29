#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class WhileTNode :
	public ConditionalTNode {
public:
	WhileTNode(int);

	void buildWhileTNode(VariableTNode, StmtListTNode);

	StmtListTNode& getBody();
private:

};

