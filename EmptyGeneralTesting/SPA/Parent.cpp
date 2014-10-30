#include "Parent.h"
#include <algorithm>
#include <utility>
#include <vector>

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

}

bool Parent::IsParent(int parentStmtIndex, int childStmtIndex) {
	pair<int, int> newParentRelationship(parentStmtIndex, childStmtIndex);

	return AlreadyInserted(newParentRelationship);

}

int Parent::GetChildOf(int parentStmtIndex) {
	return -123;
}

int Parent::GetParentOf(int childStmtIndex) {
	return -123;
}

bool Parent::AlreadyInserted(pair<int, int> newPair) {
	vector<pair<int, int>>::iterator newPairIterator = find(parentTable.begin(), parentTable.end(), newPair);

	return newPairIterator != parentTable.end();

}