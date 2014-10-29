#include "ConditionalTNode.h"

ConditionalTNode::ConditionalTNode(Type type, int lineNumber) 
	: TNode(type) 
	, StmtTNode(type, lineNumber) {
}

void ConditionalTNode::setCondition(VariableTNode condition) {
	addChild(condition);
}

VariableTNode ConditionalTNode::getCondition() {
	return TNode::typecast<VariableTNode>(getChild(0));
}