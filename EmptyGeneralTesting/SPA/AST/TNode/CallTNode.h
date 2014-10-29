#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"

class CallTNode :
	public StmtTNode {
public:
	CallTNode(StmtListTNode*, int, StmtTNode*, string);

	string getProcName();
	string getContent();

protected:

};

