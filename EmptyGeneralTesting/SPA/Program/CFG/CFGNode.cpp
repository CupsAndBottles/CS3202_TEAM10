#include "CFGNode.h"

CFGNode::CFGNode(int stmtNumber) 
	: stmtNumber(stmtNumber) {
}

const CFGNode* CFGNode::nextStmt() {
	return chooseOption(0);
}

const CFGNode* CFGNode::chooseOption(int option) {
	if (option >= children.size()) {
		return nullptr;
	} else {
		return children[option];
	}
}

void CFGNode::addOption(CFGNode* option) {
	children.push_back(option);
}