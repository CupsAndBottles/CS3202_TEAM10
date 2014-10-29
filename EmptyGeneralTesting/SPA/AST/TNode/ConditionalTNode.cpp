#include "ConditionalTNode.h"

ConditionalTNode::ConditionalTNode(StmtListTNode* directParent, Type type, int lineNumber, StmtTNode* logicalParent) 
	: TNode(directParent, type) 
	, StmtTNode(directParent, type, lineNumber, logicalParent) {
}

VariableTNode ConditionalTNode::getCondition() {
	return TNode::typecast<TNode, VariableTNode>(getChild(0));
}