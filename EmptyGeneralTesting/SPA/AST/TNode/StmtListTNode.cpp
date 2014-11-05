#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(string name)
	: ContainerTNode(StmtList) {

		buildName(name.append(":").append(enumToString(StmtList)));
}

StmtTNode& StmtListTNode::getChild(int index) {
	return dynamic_cast<StmtTNode&>(TNode::getChild(index));
}

void StmtListTNode::addChild(StmtTNode* child) {
	TNode::addChild(child);
}

vector<StmtTNode*> StmtListTNode::getStmtList() {
	vector<StmtTNode*> result;
	for (unsigned int i = 0; i < children.size(); i++) {
		result.push_back(dynamic_cast<StmtTNode*>(children[i]));
	}

	return result;
}

string StmtListTNode::getContent() {
	throwUnsupportedOperationException();
	return TNode::getContent();
}
