#pragma once

#include "TNode.h"
#include "StmtListTNode.h"

class StmtTNode :
	public virtual TNode {
public:
	StmtTNode* getParent();
	StmtTNode* getFollows();
	int getLineNumber();
protected:
	StmtTNode(StmtListTNode*, StmtTNode*, Type, int, StmtTNode*);
	int lineNumber;
	StmtTNode* logicalParent;

};

