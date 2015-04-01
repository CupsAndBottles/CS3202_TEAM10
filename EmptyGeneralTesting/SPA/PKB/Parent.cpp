#include <algorithm>
#include <utility>
#include <map>
#include <vector>
#include <iostream>

#include "Parent.h"
#include "StmtTypeTable.h"

map <int, vector<int>> Parent::parentToChildrenTable;
map <int, int> Parent::childToParentTable;
vector<vector<bool>> Parent::parentToChildrenTTable;

/** public methods **/
Parent::Parent() {
	// empty constructor

}

// Methods
void Parent::SetParent(int parentStmtIndex, int childStmtIndex) {
	if (HasNoParent(childStmtIndex) && !AlreadyInserted(parentStmtIndex, childStmtIndex) ) {
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

bool Parent::IsParentTBV(int parentStmtIndex, int childStmtIndex) {
	int totalNoOfStmts = StmtTypeTable::GetMaxStmtIndex();

	if (parentStmtIndex >= 0 && parentStmtIndex < totalNoOfStmts + 1 
		&& childStmtIndex >= 0 && childStmtIndex < totalNoOfStmts + 1) {
		return parentToChildrenTTable.at(parentStmtIndex).at(childStmtIndex);
	} else {
		return false;
	}

}

vector<int> Parent::GetParentTOf(int childStmtIndex) {
	vector<int> parentList;
	int currParent = GetParentOf(childStmtIndex);

	while (currParent != -1) {
		parentList.push_back(currParent);

		childStmtIndex = currParent;
		currParent = GetParentOf(childStmtIndex);
		
	}

	return parentList;
}

vector<int> Parent::GetChildrenTOf(int parentStmtIndex) {
	vector<int> allDescendants, 
				childrenOfCurrNode, grandChildrenOfCurrChild;

	// add this's children
	childrenOfCurrNode = GetChildrenOf(parentStmtIndex);
	allDescendants.insert(allDescendants.end(), childrenOfCurrNode.begin(), childrenOfCurrNode.end());

	// add this's children's children
	// only enter for loop if parentStmtIndex has at least 1 child
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

void Parent::CreateParentToChildrenTTable() {
	int totalNoOfStmts = StmtTypeTable::GetMaxStmtIndex();
	vector<bool> emptyRow(totalNoOfStmts + 1, false);
	parentToChildrenTTable = vector<vector<bool>>(totalNoOfStmts + 1, emptyRow);

	vector<int> childrenT;
	for (int i = 0; i < (totalNoOfStmts + 1); i++) {
		childrenT = GetChildrenTOf(i);

		for(vector<int>::iterator it = childrenT.begin(); it != childrenT.end(); it++) {
			parentToChildrenTTable.at(i).at(*it) = true;

		}
	
	}

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
	if (childToParentTable.count(childStmtIndex) != 0)
		return childToParentTable[childStmtIndex] == parentStmtIndex;
	else
		return false;
}

bool Parent::HasNoParent(int childStmtIndex) {
	// map.find() == map.end() was buggy, used count method cos no need to worry about iterator equality
	return childToParentTable.count(childStmtIndex) == 0;
}