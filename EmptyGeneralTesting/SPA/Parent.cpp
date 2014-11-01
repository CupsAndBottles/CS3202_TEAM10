#include "Parent.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>

/** public methods **/
// Default constructor
Parent::Parent() {
	// empty constructor

}

// Methods
void Parent::SetParent(int parentStmtIndex, int childStmtIndex) {
	pair<int, int> newParentRelationship(parentStmtIndex, childStmtIndex);
	
	// check if the child has more than one parent?
	if (!AlreadyInserted(newParentRelationship)) {
		parentTable.push_back(newParentRelationship);

	}
	
	// next time, check if children with > 1 parents are inserted

}

bool Parent::IsParent(int parentStmtIndex, int childStmtIndex) {
	pair<int, int> newParentRelationship(parentStmtIndex, childStmtIndex);

	return AlreadyInserted(newParentRelationship);

}

int Parent::GetParentOf(int childStmtIndex) {
	pair<int, int> checkParentRelationship;

	// sequential search for now
	for (unsigned int i = 0; i < parentTable.size(); i++) {
		checkParentRelationship = parentTable.at(i);

		if (checkParentRelationship.second == childStmtIndex) {
			return checkParentRelationship.first;

		}

	}
	return -1;
}

vector<int> Parent::GetChildrenOf(int parentStmtIndex) {
	pair<int, int> checkParentRelationship;
	vector<int> childrenList;
	
	// sequential search for now
	for (int i = 0; i < parentTable.size(); i++) {
		checkParentRelationship = parentTable.at(i);

		if (checkParentRelationship.first == parentStmtIndex) {
			childrenList.push_back(checkParentRelationship.second);

		}

	}

	return childrenList;
}

bool Parent::IsParentT(int parentStmtIndex, int childStmtIndex) {
	vector<int> childrenList = GetChildrenOf(parentStmtIndex);	// this operation is very time-consuming
	vector<int> grandChildrenList;

	for (unsigned int i = 0; i < childrenList.size(); i++) {
		if (childStmtIndex == childrenList.at(i)) {
			return true;

		} else {
			grandChildrenList = GetChildrenOf(childrenList.at(i));
			if (grandChildrenList.size() > 0) {
				if (IsParentT(childrenList.at(i), childStmtIndex)) {
					return true;
				}

			}
		}

	}

	return false;
}

vector<int> Parent::GetParentTOf(int childStmtIndex) {
	vector<int> parentList;
	int currParent;

	currParent = GetParentOf(childStmtIndex);

	while (currParent != -1) {
		parentList.push_back(currParent);

		childStmtIndex = currParent;
		currParent = GetParentOf(childStmtIndex);

	}

	return parentList;
}

vector<int> Parent::GetChildrenTOf(int parentStmtIndex) {
	vector<int> childrenList = GetChildrenOf(parentStmtIndex);
	vector<int> grandChildrenList, allDecendants;

	for (unsigned int i = 0; i < childrenList.size(); i++) {
		grandChildrenList = GetChildrenOf(childrenList.at(i));
		if (grandChildrenList.size() > 0) {
			allDecendants = GetChildrenTOf(childrenList.at(i));
			childrenList.insert(childrenList.end(), allDecendants.begin(), allDecendants.end());

		}
	
	}

	return childrenList;

}

// tells whether any parents relationships are stored
bool Parent::HasAnyParents() {
	return SizeOfParent() > 0;
}

int Parent::SizeOfParent() {
	return parentTable.size();
}

/** private methods **/
bool Parent::AlreadyInserted(pair<int, int> newPair) {
	vector<pair<int, int> >::iterator newPairIterator = find(parentTable.begin(), parentTable.end(), newPair);

	return newPairIterator != parentTable.end();

}
