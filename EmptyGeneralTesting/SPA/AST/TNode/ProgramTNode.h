#pragma once

#include "AST\TNode\ContainerTNode.h"
#include "AST\TNode\ProcedureTNode.h"

#include <deque>

class ProgramTNode :
	public ContainerTNode {
public:
	deque<ProcedureTNode> getBody();
	TNode* getDirectParent();
	ContainerTNode* getRightSibling();
private:
	ProgramTNode(string, deque<ProcedureTNode>);
};

