#include "WhileTNode.h"

WhileTNode::WhileTNode(int lineNumber) 
	: TNode(WHILE)
	, ConditionalTNode(WHILE, lineNumber) {
}

void WhileTNode::BuildWhileNode(VariableTNode* condition, StmtListTNode* loopBody) {
	SetCondition(condition);
	AddChild(loopBody);
}

StmtListTNode& WhileTNode::GetBody() {
	return dynamic_cast<StmtListTNode&>(GetChild(1));
}
