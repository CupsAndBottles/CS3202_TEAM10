#include "WhileTNode.h"

WhileTNode::WhileTNode(int lineNumber) 
	: TNode(While)
	, ConditionalTNode(While, lineNumber) {
}

void WhileTNode::buildWhileTNode(VariableTNode condition, StmtListTNode loopBody) {
	setCondition(condition);
	addChild(loopBody);
}

StmtListTNode& WhileTNode::getBody() {
	return TNode::typecast<StmtListTNode>(getChild(1));
}
