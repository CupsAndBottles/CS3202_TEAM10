#pragma once

#include "TNode.h"

class BinaryTNode : 
	public virtual TNode {
public:
	BinaryTNode(string);

	void BuildBinaryNode(TNode*, TNode*);

	virtual TNode& GetLHS();
	TNode& GetRHS();
	string GetOperator();

protected:

};

