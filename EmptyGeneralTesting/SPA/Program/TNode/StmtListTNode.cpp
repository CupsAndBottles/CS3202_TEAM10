#include "StmtListTNode.h"

StmtListTNode::StmtListTNode(string name)
	: ContainerTNode(STMT_LIST) {

		BuildName(name.append(":").append(EnumToString(STMT_LIST)));
}

StmtTNode& StmtListTNode::GetChild(unsigned int index) {
	return dynamic_cast<StmtTNode&>(TNode::GetChild(index));
}

void StmtListTNode::AddChild(StmtTNode* child) {
	TNode::AddChild(child);
}

vector<StmtTNode*> StmtListTNode::GetStmtList() {
	vector<StmtTNode*> result;
	for (unsigned unsigned int i = 0; i < children.size(); i++) {
		result.push_back(dynamic_cast<StmtTNode*>(children[i]));
	}

	return result;
}

string StmtListTNode::GetContent() {
	ThrowUnsupportedOperationException();
	return TNode::GetContent();
}
