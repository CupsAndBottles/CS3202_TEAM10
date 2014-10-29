#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(string name)
	: ContainerTNode(StmtList) {

		buildName(name.append(":").append(enumToString(StmtList)));
}

void StmtListTNode::addChild(StmtTNode child) {
	TNode::addChild(child);
}

vector<StmtTNode> StmtListTNode::getStmtList() {
	return vectorCaster<StmtTNode>(getChildren());
}
