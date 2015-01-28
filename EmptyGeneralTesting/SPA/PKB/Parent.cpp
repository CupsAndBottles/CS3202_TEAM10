#include "Parent.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>

vector<pair<unsigned int, unsigned int>> Parent::parentTable;

/** public methods **/
// Default constructor
Parent::Parent() {
	// empty constructor

}

// Methods
void Parent::SetParent(unsigned int parentStmtIndex, unsigned int childStmtIndex) {
	pair<unsigned int, unsigned int> newParentRelationship(parentStmtIndex, childStmtIndex);
	
	// check if the child has more than one parent?
	if (!AlreadyInserted(newParentRelationship)) {
		parentTable.push_back(newParentRelationship);

	}
	
	// next time, check if children with > 1 parents are inserted

}

bool Parent::IsParent(unsigned int parentStmtIndex, unsigned int childStmtIndex) {
	pair<unsigned int, unsigned int> newParentRelationship(parentStmtIndex, childStmtIndex);

	return AlreadyInserted(newParentRelationship);

}

unsigned int Parent::GetParentOf(unsigned int childStmtIndex) {
	pair<unsigned int, unsigned int> checkParentRelationship;

	// sequential search for now
	for (unsigned unsigned int i = 0; i < parentTable.size(); i++) {
		checkParentRelationship = parentTable.at(i);

		if (checkParentRelationship.second == childStmtIndex) {
			return checkParentRelationship.first;

		}

	}
	return -1;
}

vector<unsigned int> Parent::GetChildrenOf(unsigned int parentStmtIndex) {
	pair<unsigned int, unsigned int> checkParentRelationship;
	vector<unsigned int> childrenList;
	
	// sequential search for now
	for (unsigned int i = 0; i < parentTable.size(); i++) {
		checkParentRelationship = parentTable.at(i);

		if (checkParentRelationship.first == parentStmtIndex) {
			childrenList.push_back(checkParentRelationship.second);

		}

	}

	return childrenList;
}

bool Parent::IsParentT(unsigned int parentStmtIndex, unsigned int childStmtIndex) {
	vector<unsigned int> childrenList = GetChildrenOf(parentStmtIndex);	// this operation is very time-consuming
	vector<unsigned int> grandChildrenList;

	for (unsigned unsigned int i = 0; i < childrenList.size(); i++) {
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

vector<unsigned int> Parent::GetParentTOf(unsigned int childStmtIndex) {
	vector<unsigned int> parentList;
	unsigned int currParent;

	currParent = GetParentOf(childStmtIndex);

	while (currParent != -1) {
		parentList.push_back(currParent);

		childStmtIndex = currParent;
		currParent = GetParentOf(childStmtIndex);

	}

	return parentList;
}

vector<unsigned int> Parent::GetChildrenTOf(unsigned int parentStmtIndex) {
	vector<unsigned int> childrenList = GetChildrenOf(parentStmtIndex);
	vector<unsigned int> grandChildrenList, allDecendants;

	for (unsigned unsigned int i = 0; i < childrenList.size(); i++) {
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

unsigned int Parent::SizeOfParent() {
	return parentTable.size();
}

void Parent::ClearData() {
	parentTable.clear();
}

/** private methods **/
bool Parent::AlreadyInserted(pair<unsigned int, unsigned int> newPair) {
	vector<pair<unsigned int, unsigned int> >::iterator newPairIterator = find(parentTable.begin(), parentTable.end(), newPair);

	return newPairIterator != parentTable.end();

}
