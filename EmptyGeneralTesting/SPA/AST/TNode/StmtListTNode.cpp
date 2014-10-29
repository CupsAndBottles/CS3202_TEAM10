#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(TNode* parent, StmtListTNode* rightSibling, string name, vector<StmtTNode> stmtList)
	: ContainerTNode(parent, rightSibling, StmtList, vectorCaster<StmtTNode, TNode>(stmtList)) {

		buildName(name.append(":").append(enumToString(StmtList)));
}

vector<StmtTNode> StmtListTNode::getStmtList() {
	return vectorCaster<TNode, StmtTNode>(getChildren());
}
