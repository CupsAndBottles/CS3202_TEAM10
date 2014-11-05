#pragma once

#include "StmtTNode.h"
#include "StmtListTNode.h"

class CallTNode :
	public StmtTNode {
public:
	CallTNode(int, string);

	string getProcName();

protected:

};

