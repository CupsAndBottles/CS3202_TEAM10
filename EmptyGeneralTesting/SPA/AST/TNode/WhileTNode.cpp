#include "WhileTNode.h"


WhileTNode::WhileTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, VariableTNode condition, StmtListTNode body) 
	: TNode(directParent, rightSibling, TNode::While)
	, ConditionalTNode(directParent, rightSibling, TNode::While, lineNumber, logicalParent, condition) {

	addChild(body);
}

StmtListTNode& WhileTNode::getBody() {
	return TNode::typecast<TNode, StmtListTNode>(getChild(1));
}
