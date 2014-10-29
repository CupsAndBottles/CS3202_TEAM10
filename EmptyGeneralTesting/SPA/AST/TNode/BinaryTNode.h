#pragma once

#include "TNode.h"

class BinaryTNode : 
	public virtual TNode {
public:
	BinaryTNode(TNode*, string);

	virtual TNode& getLHS();
	TNode& getRHS();
	string getContent();
	string getOperator();

protected:

};

