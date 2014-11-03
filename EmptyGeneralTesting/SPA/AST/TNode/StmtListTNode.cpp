#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(string name)
	: ContainerTNode(StmtList) {

		buildName(name.append(":").append(enumToString(StmtList)));
}

StmtTNode& StmtListTNode::getChild(int index) {
	return typecast<StmtTNode&>(TNode(getChild(index)));
}

void StmtListTNode::addChild(StmtTNode child) {
	TNode::addChild(child);
}

vector<StmtTNode> StmtListTNode::getStmtList() {
	return vectorCaster<StmtTNode>(getChildren());
}
