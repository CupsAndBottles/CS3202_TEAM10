#pragma once

#include "ConditionalTNode.h"
#include "StmtListTNode.h"

class IfTNode :
	public ConditionalTNode {
public:
	IfTNode(int);

	void buildIfTNode(VariableTNode, StmtListTNode, StmtListTNode);

	StmtListTNode& getThenBody();
	StmtListTNode& getElseBody();

private:

};

