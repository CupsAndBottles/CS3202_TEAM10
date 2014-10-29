#include "IfTNode.h"

IfTNode::IfTNode(StmtListTNode* directParent, int lineNumber, StmtTNode* logicalParent) 
	: TNode(directParent, If)
	, ConditionalTNode(directParent, If, lineNumber, logicalParent) {

	buildName(enumToString(If));
}

StmtListTNode& IfTNode::getThenBody() {
	return typecast<TNode, StmtListTNode>(getChild(1));
}

StmtListTNode& IfTNode::getElseBody() {
	return typecast<TNode, StmtListTNode>(getChild(2));
}
