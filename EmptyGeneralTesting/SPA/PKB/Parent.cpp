#include <algorithm>
#include <utility>
#include <map>
#include <vector>

#include "Parent.h"

map <int, vector<int>> Parent::parentToChildrenTable;
map <int, int> Parent::childToParentTable;

/** public methods **/
Parent::Parent() {
	// empty constructor

}

// Methods
void Parent::SetParent(int parentStmtIndex, int childStmtIndex) {
	if (!AlreadyInserted(parentStmtIndex, childStmtIndex) && HasNoParent(childStmtIndex)) {
		parentToChildrenTable[parentStmtIndex].push_back(childStmtIndex);
		childToParentTable[childStmtIndex] = parentStmtIndex;

	}

}

bool Parent::IsParent(int parentStmtIndex, int childStmtIndex) {
	return AlreadyInserted(parentStmtIndex, childStmtIndex);

}

int Parent::GetParentOf(int childStmtIndex) {
	if (!HasNoParent(childStmtIndex)) {
		return childToParentTable[childStmtIndex];

	} else {
		return -1;
	
	}
}

vector<int> Parent::GetChildrenOf(int parentStmtIndex) {
	return parentToChildrenTable[parentStmtIndex];

}

bool Parent::IsParentT(int parentStmtIndex, int childStmtIndex) {
	int currChild = childStmtIndex;

	while (!HasNoParent(currChild)) {
		if (childToParentTable[currChild] == parentStmtIndex) {
			return true;

		}

		currChild = childToParentTable[currChild];

	}

	return false;

}

vector<int> Parent::GetParentTOf(int childStmtIndex) {
	vector<int> parentList;
	int currParent;

	while (currParent != -1) {
		currParent = GetParentOf(childStmtIndex);
		parentList.push_back(currParent);

		childStmtIndex = currParent;
		
	}

	return parentList;
}

vector<int> Parent::GetChildrenTOf(int parentStmtIndex) {
	vector<int> allDescendants, 
				childrenOfCurrNode, grandChildrenOfCurrChild;

	childrenOfCurrNode = GetChildrenOf(parentStmtIndex);
	allDescendants.push_back(parentStmtIndex);

	for (unsigned int i = 0; i < childrenOfCurrNode.size(); i++) {
		grandChildrenOfCurrChild = GetChildrenTOf(childrenOfCurrNode.at(i));
		allDescendants.insert(allDescendants.end(), grandChildrenOfCurrChild.begin(), grandChildrenOfCurrChild.end());
	
	}
	
	return allDescendants;

	// each recursive iteration inserts the subtree whose root is the currNode into allDescendants

}

// tells whether any parents relationships are stored
bool Parent::HasAnyParents() {
	return SizeOfParent() > 0;
}

int Parent::SizeOfParent() {
	return childToParentTable.size();
}

void Parent::ClearData() {
	parentToChildrenTable.clear();
	childToParentTable.clear();
}

/** private methods **/
bool Parent::AlreadyInserted(int parentStmtIndex, int childStmtIndex) {
	return childToParentTable[childStmtIndex] == parentStmtIndex;
}

bool Parent::HasNoParent(int childStmtIndex) {
	return childToParentTable.find(childStmtIndex) == childToParentTable.end();
}
