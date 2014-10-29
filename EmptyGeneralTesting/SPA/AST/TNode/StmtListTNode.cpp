#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(TNode* parent, string name)
	: ContainerTNode(parent, StmtList) {

		buildName(name.append(":").append(enumToString(StmtList)));
}

vector<StmtTNode> StmtListTNode::getStmtList() {
	return vectorCaster<TNode, StmtTNode>(getChildren());
}
