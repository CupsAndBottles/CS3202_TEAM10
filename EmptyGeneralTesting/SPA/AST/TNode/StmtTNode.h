#pragma once

#include "TNode.h"

class StmtTNode :
	public virtual TNode {
public:
	StmtTNode(TNode*, Type, int, StmtTNode*);

	StmtTNode* getParent();
	StmtTNode* getFollows();
	int getLineNumber();

protected:
	int lineNumber;
	StmtTNode* logicalParent;

};

