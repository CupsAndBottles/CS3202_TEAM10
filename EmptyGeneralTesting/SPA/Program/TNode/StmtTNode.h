#pragma once

#include "TNode.h"

class StmtTNode :
	public virtual TNode {
public:
	void SetParent(StmtTNode*);

	StmtTNode* GetParent();
	StmtTNode* GetFollows();
	unsigned int GetLineNumber();
	virtual string GetContent();

protected:
	StmtTNode(Type, unsigned int);

	unsigned int lineNumber;
	StmtTNode* logicalParent;

};

