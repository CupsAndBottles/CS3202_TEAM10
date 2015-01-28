#include "ConditionalTNode.h"

ConditionalTNode::ConditionalTNode(Type type, unsigned int lineNumber) 
	: TNode(type) 
	, StmtTNode(type, lineNumber) {
}

void ConditionalTNode::SetCondition(VariableTNode* condition) {
	AddChild(condition);
}

VariableTNode ConditionalTNode::GetCondition() {
	return dynamic_cast<VariableTNode&>(GetChild(0));
}