#pragma once

#include "TNode.h"

class StmtTNode :
	public virtual TNode {
public:
	StmtTNode* getParent();
	StmtTNode* getFollows();
	int getLineNumber();
protected:
	StmtTNode(TNode*, StmtTNode*, Type, int, StmtTNode*);
	int lineNumber;
	StmtTNode* logicalParent;

};

