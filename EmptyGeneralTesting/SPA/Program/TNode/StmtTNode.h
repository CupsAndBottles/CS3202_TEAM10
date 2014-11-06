#pragma once

#include "TNode.h"

class StmtTNode :
	public virtual TNode {
public:
	void SetParent(StmtTNode*);

	StmtTNode* GetParent();
	StmtTNode* GetFollows();
	int GetLineNumber();
	virtual string GetContent();

protected:
	StmtTNode(Type, int);

	int lineNumber;
	StmtTNode* logicalParent;

};

