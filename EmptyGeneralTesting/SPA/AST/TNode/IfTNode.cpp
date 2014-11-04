#include "IfTNode.h"

IfTNode::IfTNode(int lineNumber) 
	: TNode(If)
	, ConditionalTNode(If, lineNumber) {

	buildName(enumToString(If));
}

void IfTNode::buildIfTNode(VariableTNode condition, StmtListTNode thenBranch, StmtListTNode elseBranch) {
	setCondition(condition);
	addChild(thenBranch);
	addChild(elseBranch);
}

StmtListTNode& IfTNode::getThenBody() {
	return dynamic_cast<StmtListTNode&>(getChild(1));
}

StmtListTNode& IfTNode::getElseBody() {
	return dynamic_cast<StmtListTNode&>(getChild(2));
}
