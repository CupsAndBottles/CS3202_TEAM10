#include "ConditionalTNode.h"


ConditionalTNode::ConditionalTNode(StmtListTNode* directParent, StmtTNode* rightSibling, Type type, int lineNumber, StmtTNode* logicalParent, VariableTNode condition) 
	: TNode(directParent, rightSibling, type) 
	, StmtTNode(directParent, rightSibling, type, lineNumber, logicalParent) {
	addChild(condition);
}

VariableTNode ConditionalTNode::getCondition() {
	return TNode::typecast<TNode, VariableTNode>(getChild(0));
}