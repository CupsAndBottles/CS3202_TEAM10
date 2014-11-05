#pragma once

#include "TNode.h"

class BinaryTNode : 
	public virtual TNode {
public:
	BinaryTNode(string);

	void buildBinaryNode(TNode*, TNode*);

	virtual TNode& getLHS();
	TNode& getRHS();
	string getOperator();

protected:

};

