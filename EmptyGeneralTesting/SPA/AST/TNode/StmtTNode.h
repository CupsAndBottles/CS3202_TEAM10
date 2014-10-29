#pragma once

#include "TNode.h"

class StmtTNode :
	public virtual TNode {
public:
	void setParent(StmtTNode*);

	StmtTNode* getParent();
	StmtTNode* getFollows();
	int getLineNumber();

protected:
	StmtTNode(Type, int);

	int lineNumber;
	StmtTNode* logicalParent;

};

