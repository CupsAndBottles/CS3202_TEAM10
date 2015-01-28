#include <algorithm>
#include <utility>
#include <map>
#include <vector>

<<<<<<< HEAD
#include "Parent.h"

map <int, vector<int>> Parent::parentToChildrenTable;
map <int, int> Parent::childToParentTable;
=======
vector<pair<unsigned int, unsigned int>> Parent::parentTable;
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

/** public methods **/
Parent::Parent() {
	// empty constructor

}

// Methods
<<<<<<< HEAD
void Parent::SetParent(int parentStmtIndex, int childStmtIndex) {
	if (!AlreadyInserted(parentStmtIndex, childStmtIndex) && HasNoParent(childStmtIndex)) {
		parentToChildrenTable[parentStmtIndex].push_back(childStmtIndex);
		childToParentTable[childStmtIndex] = parentStmtIndex;
=======
void Parent::SetParent(unsigned int parentStmtIndex, unsigned int childStmtIndex) {
	pair<unsigned int, unsigned int> newParentRelationship(parentStmtIndex, childStmtIndex);
	
	// check if the child has more than one parent?
	if (!AlreadyInserted(newParentRelationship)) {
		parentTable.push_back(newParentRelationship);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	}

}

<<<<<<< HEAD
bool Parent::IsParent(int parentStmtIndex, int childStmtIndex) {
	return AlreadyInserted(parentStmtIndex, childStmtIndex);

}

int Parent::GetParentOf(int childStmtIndex) {
	if (!HasNoParent(childStmtIndex)) {
		return childToParentTable[childStmtIndex];
=======
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
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	} else {
		return -1;
	
	}
}

<<<<<<< HEAD
vector<int> Parent::GetChildrenOf(int parentStmtIndex) {
	return parentToChildrenTable[parentStmtIndex];
=======
vector<unsigned int> Parent::GetChildrenOf(unsigned int parentStmtIndex) {
	pair<unsigned int, unsigned int> checkParentRelationship;
	vector<unsigned int> childrenList;
	
	// sequential search for now
	for (unsigned int i = 0; i < parentTable.size(); i++) {
		checkParentRelationship = parentTable.at(i);

		if (checkParentRelationship.first == parentStmtIndex) {
			childrenList.push_back(checkParentRelationship.second);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

}

<<<<<<< HEAD
bool Parent::IsParentT(int parentStmtIndex, int childStmtIndex) {
	int currChild = childStmtIndex;

	while (!HasNoParent(currChild)) {
		if (childToParentTable[currChild] == parentStmtIndex) {
=======
bool Parent::IsParentT(unsigned int parentStmtIndex, unsigned int childStmtIndex) {
	vector<unsigned int> childrenList = GetChildrenOf(parentStmtIndex);	// this operation is very time-consuming
	vector<unsigned int> grandChildrenList;

	for (unsigned unsigned int i = 0; i < childrenList.size(); i++) {
		if (childStmtIndex == childrenList.at(i)) {
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
			return true;

		}

		currChild = childToParentTable[currChild];

	}

	return false;

}

vector<unsigned int> Parent::GetParentTOf(unsigned int childStmtIndex) {
	vector<unsigned int> parentList;
	unsigned int currParent;

	while (currParent != -1) {
		currParent = GetParentOf(childStmtIndex);
		parentList.push_back(currParent);

		childStmtIndex = currParent;
		
	}

	return parentList;
}

<<<<<<< HEAD
vector<int> Parent::GetChildrenTOf(int parentStmtIndex) {
	vector<int> allDescendants, 
				childrenOfCurrNode, grandChildrenOfCurrChild;

	childrenOfCurrNode = GetChildrenOf(parentStmtIndex);
	allDescendants.push_back(parentStmtIndex);
=======
vector<unsigned int> Parent::GetChildrenTOf(unsigned int parentStmtIndex) {
	vector<unsigned int> childrenList = GetChildrenOf(parentStmtIndex);
	vector<unsigned int> grandChildrenList, allDecendants;

	for (unsigned unsigned int i = 0; i < childrenList.size(); i++) {
		grandChildrenList = GetChildrenOf(childrenList.at(i));
		if (grandChildrenList.size() > 0) {
			allDecendants = GetChildrenTOf(childrenList.at(i));
			childrenList.insert(childrenList.end(), allDecendants.begin(), allDecendants.end());
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

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

<<<<<<< HEAD
int Parent::SizeOfParent() {
	return childToParentTable.size();
=======
unsigned int Parent::SizeOfParent() {
	return parentTable.size();
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
}

void Parent::ClearData() {
	parentToChildrenTable.clear();
	childToParentTable.clear();
}

/** private methods **/
<<<<<<< HEAD
bool Parent::AlreadyInserted(int parentStmtIndex, int childStmtIndex) {
	return childToParentTable[childStmtIndex] == parentStmtIndex;
}
=======
bool Parent::AlreadyInserted(pair<unsigned int, unsigned int> newPair) {
	vector<pair<unsigned int, unsigned int> >::iterator newPairIterator = find(parentTable.begin(), parentTable.end(), newPair);

	return newPairIterator != parentTable.end();
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

bool Parent::HasNoParent(int childStmtIndex) {
	return childToParentTable.find(childStmtIndex) == childToParentTable.end();
}
