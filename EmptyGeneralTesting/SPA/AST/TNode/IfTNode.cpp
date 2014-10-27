#include "IfTNode.h"


IfTNode::IfTNode(StmtListTNode* directParent, StmtTNode* rightSibling, int lineNumber, StmtTNode* logicalParent, VariableTNode condition, StmtListTNode thenBranch, StmtListTNode elseBranch) 
	: TNode(directParent, rightSibling, TNode::If)
	, ConditionalTNode(directParent, rightSibling, TNode::If, lineNumber, logicalParent, condition) {

	buildName(enumToString(TNode::If));
	addChild(thenBranch);
	addChild(elseBranch);
}

StmtListTNode& IfTNode::getThenBody() {
	return TNode::typecast<TNode, StmtListTNode>(getChild(1));
}

StmtListTNode& IfTNode::getElseBody() {
	return TNode::typecast<TNode, StmtListTNode>(getChild(2));
}
