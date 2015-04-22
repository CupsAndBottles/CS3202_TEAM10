#include "Sibling.h"
#include "NodeTypeTable.h"

#include <set>

Sibling::Sibling() {
}

bool Sibling::IsSibling(int nodeOne, int nodeTwo) {
	if (nodeOne == nodeTwo) throw (string) "Nodes must be different!";
	TNode* parentNode = NodeTypeTable::GetPtrToNode(nodeOne)->GetDirectParent();
	if (parentNode != nullptr) {
		for each (TNode* child in parentNode->GetChildren()) {
			if (child->GetNodeIndex() == nodeTwo) {
				return true;
			}
		}
	}
	return false;
}

bool Sibling::IsSibling(int nodeOne, NodeType nodeTwo) {
	TNode* parentNode = NodeTypeTable::GetPtrToNode(nodeOne)->GetDirectParent();
	if (parentNode != nullptr) {
		for each (TNode* child in parentNode->GetChildren()) {
			if (NodeTypeTable::CheckIfNodeOfType(child->GetNodeIndex(), nodeTwo)) {
				return true;
			}
		}
	}
	return false;
}

bool Sibling::IsSibling(NodeType nodeOne, int nodeTwo) {
	for each (int node in NodeTypeTable::GetAllNodesOfType(nodeOne)) {
		if (IsSibling(node, nodeTwo)) return true;
	}

	return false;
}

bool Sibling::IsSibling(NodeType nodeOne, NodeType nodeTwo) {
	for each (int node in NodeTypeTable::GetAllNodesOfType(nodeOne)) {
		if (IsSibling(node, nodeTwo)) return true;
	}

	return false;
}

vector<int> Sibling::GetSiblings(int node) {
	vector<int> results;
	TNode* parentNode = NodeTypeTable::GetPtrToNode(node)->GetDirectParent();
	if (parentNode != nullptr) {
		for each (TNode* child in parentNode->GetChildren()) {
			int childNodeIndex = child->GetNodeIndex();
			if (childNodeIndex != node) {
				results.push_back(childNodeIndex);
			}
		}
	}

	return results;
}

vector<int> Sibling::GetSiblings(NodeType node) {
	set<int> results;

	for each (int n in NodeTypeTable::GetAllNodesOfType(node)) {
		vector<int> tempResult = GetSiblings(n);
		results.insert(results.begin(), results.end());
	}
	return vector<int>(results.begin(), results.end());
}
