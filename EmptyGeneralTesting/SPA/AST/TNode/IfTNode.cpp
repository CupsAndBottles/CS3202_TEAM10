#include "IfTNode.h"

IfTNode::IfTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, VariableTNode condition, StmtListTNode thenBranch, StmtListTNode elseBranch) 
	: TNode(directParent, rightSibling, If)
	, ConditionalTNode(directParent, rightSibling, If, lineNumber, logicalParent, condition) {

	buildName(enumToString(If));
	addChild(thenBranch);
	addChild(elseBranch);
}

StmtListTNode& IfTNode::getThenBody() {
	return typecast<TNode, StmtListTNode>(getChild(1));
}

StmtListTNode& IfTNode::getElseBody() {
	return typecast<TNode, StmtListTNode>(getChild(2));
}
