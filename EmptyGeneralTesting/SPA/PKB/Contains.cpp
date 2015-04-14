#include "Contains.h"
#include "NodeTypeTable.h"
#include "VarTable.h"

#include <algorithm>
#include <set>

Contains::Contains() {
}

bool Contains::IsContains(int nodeContaining, int nodeContained) {
	vector<TNode*> children = NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren();
	TNode* containedNode = NodeTypeTable::GetPtrToNode(nodeContained);

	return (find(children.begin(), children.end(), containedNode) != children.end());
}

bool Contains::IsContains(int nodeContaining, NodeType nodetypeContained) {
	for each (TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
		if (NodeTypeTable::GetNodeTypeOf(child->GetNodeIndex()) == nodetypeContained) {
			return true;
		}
	}
	return false;
}

bool Contains::IsContains(NodeType nodetypeContaining, NodeType nodetypeContained) {
	for each (int node in NodeTypeTable::GetAllNodesOfType(nodetypeContaining)) {
		if (IsContains(node, nodetypeContained)) {
			return true;
		}
	}
	return false;
}

bool Contains::IsContains(NodeType nodetypeContaining, int nodeContained) {
	for each (int node in NodeTypeTable::GetAllNodesOfType(nodetypeContaining)) {
		if (IsContains(node, nodeContained)) {
			return true;
		}
	}
	return false;
}


bool Contains::IsContainsVar(int nodeContaining, int varIndex) {
	for each (TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
		if (child->GetType() == VARIABLE) {
			if (VarTable::GetIndexOfVar(child->GetContent()) == varIndex) {
				return true;
			}
		}
	}
	return false;
}

bool Contains::IsContainsConst(int nodeContaining, int constant) {
	for each (TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
		if (child->GetType() == CONSTANT) {
			if (stoi(child->GetContent()) == constant) {
				return true;
			}
		}
	}
	return false;
}

bool Contains::IsContainsVar(NodeType nodetypeContaining, int varIndex) {
	for each (int nodeContaining in NodeTypeTable::GetAllNodesOfType(nodetypeContaining)) {
		for each (TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
			if (child->GetType() == VARIABLE) {
				if (VarTable::GetIndexOfVar(child->GetContent()) == varIndex) {
					return true;
				}
			}
		}
	}

	return false;
}

bool Contains::IsContainsConst(NodeType nodetypeContaining, int constant) {
	for each (int nodeContaining in NodeTypeTable::GetAllNodesOfType(nodetypeContaining)) {
		for each (TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
			if (child->GetType() == CONSTANT) {
				if (stoi(child->GetContent()) == constant) {
					return true;
				}
			}
		}
	}

	return false;
}


int Contains::GetNodeContaining(int nodeContained) {
	return NodeTypeTable::GetPtrToNode(nodeContained)->GetDirectParent()->GetNodeIndex();
}

vector<int> Contains::GetNodesContained(int nodeContaining) {
	vector<int> result;
	for each(TNode* child in NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren()) {
		result.push_back(child->GetNodeIndex());
	}
	return result;
}

vector<int> Contains::GetNodesContaining(NodeType nodetypeContained) {
	set<int> result;
	for each(int node in NodeTypeTable::GetAllNodesOfType(nodetypeContained)) {
		result.insert(NodeTypeTable::GetPtrToNode(node)->GetDirectParent()->GetNodeIndex());
	}
	return vector<int>(result.begin(), result.end());
}

vector<int> Contains::GetNodesContained(NodeType nodetypeContaining) {
	set<int> result;
	for each(int node in NodeTypeTable::GetAllNodesOfType(nodetypeContaining)) {
		for each(TNode* child in NodeTypeTable::GetPtrToNode(node)->GetChildren()) {
			result.insert(child->GetNodeIndex());
		}
	}
	return vector<int>(result.begin(), result.end());
}

bool IsContainsT(TNode* nodeContaining, TNode* nodeContained) {
	if (nodeContaining == nodeContained) return true; // terminating condition
	for each (TNode* child in nodeContaining->GetChildren) {
		if (IsContainsT(child, nodeContained)) return true;
	}
	return false;
}

bool Contains::IsContainsT(int nodeContaining, int nodeContained) {
	vector<TNode*> children = NodeTypeTable::GetPtrToNode(nodeContaining)->GetChildren();
	TNode* containedNode = NodeTypeTable::GetPtrToNode(nodeContained);

}

bool Contains::IsContainsT(NodeType nodetypeContaining, NodeType nodetypeContained) {

}

bool Contains::IsContainsT(int nodeContaining, NodeType nodetypeContained) {

}

bool Contains::IsContainsT(NodeType nodetypeContaining, int nodeContained) {

}


vector<int> GetNodesContainingT(int nodeContained) {

}

vector<int> GetNodesContainedT(int nodeContaining) {

}

vector<int> GetNodesContainingT(NodeType nodetypeContained) {

}

vector<int> GetNodesContainedT(NodeType nodetypeContaining) {

}


// helpers
vector<int> FilterNodesBy(vector<int> nodes, NodeType filterType) {

}

bool DoesNodeNumberExistIn(vector<int> nodes, int nodeIndex) {

}


// specialisations, feel free to add your own or make them
bool IsContainsStmt(NodeType nodetypeContaining, int stmtNumber) {

}

bool IsStmtContains(int stmtNumber, NodeType nodetypeContained) {

}

