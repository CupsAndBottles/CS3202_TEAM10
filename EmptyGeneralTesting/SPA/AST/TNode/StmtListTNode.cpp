#include "StmtListTNode.h"


StmtListTNode::StmtListTNode(string name, deque<StmtTNode> stmtList, TNode* parent, StmtListTNode* rightSibling) 
	: ContainerTNode(TNode::StmtList, name + ":StmtList", TNode::dequeCaster<StmtTNode, TNode>(stmtList), parent, rightSibling) {
}

deque<StmtTNode> StmtListTNode::getStmtList() {
	return TNode::dequeCaster<TNode, StmtTNode>(children);
}
