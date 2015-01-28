#include <algorithm>
#include <utility>
#include <map>
#include <vector>

<<<<<<< HEAD
#include "Follows.h"

map <int, int> Follows::beforeToAfterTable;
map <int, int> Follows::afterToBeforeTable;
=======
vector<pair<unsigned int, unsigned int>> Follows::followsTable;
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

/** public methods **/
Follows::Follows() {
	// empty constructor
}

// Methods
<<<<<<< HEAD
void Follows::SetFollows(int stmtBefore, int stmtAfter) {
	if (NoRelationshipConflicts(stmtBefore, stmtAfter)) {
		beforeToAfterTable[stmtBefore] = stmtAfter;
		afterToBeforeTable[stmtAfter] = stmtBefore;
=======
void Follows::SetFollows(unsigned int stmtBefore, unsigned int stmtAfter) {
	pair<unsigned int, unsigned int> newFollowsRelationship(stmtBefore, stmtAfter);
	
	if (!AlreadyInserted(newFollowsRelationship)) {
		followsTable.push_back(newFollowsRelationship);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	}

}

<<<<<<< HEAD
bool Follows::IsFollows(int stmtBefore, int stmtAfter) {
	return beforeToAfterTable[stmtBefore] == stmtAfter;

}

int Follows::GetFollowsBefore(int stmtAfter) {
	if(!HasNoStmtBefore(stmtAfter)) {
		return afterToBeforeTable[stmtAfter];

	} else {
		return -1;
=======
bool Follows::IsFollows (unsigned int stmtBefore, unsigned int stmtAfter) {
	pair<unsigned int, unsigned int> newFollowsRelationship(stmtBefore, stmtAfter);

	return AlreadyInserted(newFollowsRelationship);

}

unsigned int Follows::GetFollowsBefore(unsigned int stmtAfter) {
	pair<unsigned int, unsigned int> checkFollowsRelationship;

	// sequential search for now
	for (unsigned unsigned int i = 0; i < followsTable.size(); i++) {
		checkFollowsRelationship = followsTable.at(i);

		if (checkFollowsRelationship.second == stmtAfter) {
			return checkFollowsRelationship.first;
		
		}
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	}

}

<<<<<<< HEAD
int Follows::GetFollowsAfter(int stmtBefore) {
	if(!HasNoStmtAfter(stmtBefore)) {
		return beforeToAfterTable[stmtBefore];

	} else {
		return -1;
=======
unsigned int Follows::GetFollowsAfter(unsigned int stmtBefore) {
	pair<unsigned int, unsigned int> checkFollowsRelationship;

	// sequential search for now
	for (unsigned unsigned int i = 0; i < followsTable.size(); i++) {
		checkFollowsRelationship = followsTable.at(i);

		if (checkFollowsRelationship.first == stmtBefore) {
			return checkFollowsRelationship.second;
		
		}
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	}

}

<<<<<<< HEAD
bool Follows::IsFollowsT(int stmtBefore, int stmtAfter) {
	int currBefore = stmtBefore;
=======
bool Follows::IsFollowsT(unsigned int stmtBefore, unsigned int stmtAfter) {
	if (IsFollows(stmtBefore, stmtAfter)) {
		return true;

	} else {
		unsigned int stmtAfterBefore = GetFollowsAfter(stmtBefore);	// very time-consuming

		while (stmtAfterBefore != -1) {
			if (stmtAfterBefore == stmtAfter) {
				return true;
			}
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	while (!HasNoStmtAfter(currBefore)) {
		if (beforeToAfterTable[currBefore] == stmtAfter) {
			return true;

		}

		currBefore = beforeToAfterTable[currBefore];
	
	}

	return false;

}

<<<<<<< HEAD
vector<int> Follows::GetFollowsTBefore(int stmtAfter) {
	vector<int> beforeList;
	int stmtBefore = GetFollowsBefore(stmtAfter);

=======
vector<unsigned int> Follows::GetFollowsTBefore(unsigned int stmtAfter) {
	vector<unsigned int> beforeList;

	unsigned int stmtBefore = GetFollowsBefore(stmtAfter);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
	while (stmtBefore != -1) {
		beforeList.push_back(stmtBefore);

		stmtAfter = stmtBefore;
		stmtBefore = GetFollowsBefore(stmtAfter);
	
	}

	return beforeList;
}

vector<unsigned int> Follows::GetFollowsTAfter(unsigned int stmtBefore) {
	vector<unsigned int> afterList;

	unsigned int stmtAfter = GetFollowsAfter(stmtBefore);
	while (stmtAfter != -1) {
		afterList.push_back(stmtAfter);

		stmtBefore = stmtAfter;
		stmtAfter = GetFollowsAfter(stmtBefore);
	
	}


	return afterList;
}

bool Follows::HasAnyFollows() {
	return SizeOfFollows() > 0;
}

<<<<<<< HEAD
int Follows::SizeOfFollows() {
	return beforeToAfterTable.size();
}

void Follows::ClearData() {
	beforeToAfterTable.clear();
	afterToBeforeTable.clear();
=======
unsigned int Follows::SizeOfFollows() {
	return followsTable.size();
}

/** private methods **/
bool Follows::AlreadyInserted(pair<unsigned int, unsigned int> newPair) {
	vector<pair<unsigned int, unsigned int>>::iterator newPairIterator = find(followsTable.begin(), followsTable.end(), newPair);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

}

/** private methods **/
bool Follows::NoRelationshipConflicts(int stmtBefore, int stmtAfter) {
	return HasNoStmtAfter(stmtBefore) && HasNoStmtBefore(stmtAfter);

}

bool Follows::HasNoStmtAfter(int stmtBefore) {
	return beforeToAfterTable.find(stmtBefore) == beforeToAfterTable.end();
}

bool Follows::HasNoStmtBefore(int stmtAfter) {
	return afterToBeforeTable.find(stmtAfter) == afterToBeforeTable.end();
}