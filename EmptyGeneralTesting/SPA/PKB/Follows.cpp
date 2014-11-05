#include "Follows.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

/** public methods **/
// Default constructor
Follows::Follows() {
	// empty constructor
}

// Methods
void Follows::SetFollows(int stmtBefore, int stmtAfter) {
	pair<int, int> newFollowsRelationship(stmtBefore, stmtAfter);
	
	if (!AlreadyInserted(newFollowsRelationship)) {
		followsTable.push_back(newFollowsRelationship);

	}

	// next time check also that no 2 stmts have >1 follows before and >1 follows after

}

bool Follows::IsFollows (int stmtBefore, int stmtAfter) {
	pair<int, int> newFollowsRelationship(stmtBefore, stmtAfter);

	return AlreadyInserted(newFollowsRelationship);

}

int Follows::GetFollowsBefore(int stmtAfter) {
	pair<int, int> checkFollowsRelationship;

	// sequential search for now
	for (unsigned int i = 0; i < followsTable.size(); i++) {
		checkFollowsRelationship = followsTable.at(i);

		if (checkFollowsRelationship.second == stmtAfter) {
			return checkFollowsRelationship.first;
		
		}

	}

	return -1;

}

int Follows::GetFollowsAfter(int stmtBefore) {
	pair<int, int> checkFollowsRelationship;

	// sequential search for now
	for (unsigned int i = 0; i < followsTable.size(); i++) {
		checkFollowsRelationship = followsTable.at(i);

		if (checkFollowsRelationship.first == stmtBefore) {
			return checkFollowsRelationship.second;
		
		}

	}

	return -1;

}

bool Follows::IsFollowsT(int stmtBefore, int stmtAfter) {
	if (IsFollows(stmtBefore, stmtAfter)) {
		return true;

	} else {
		int stmtAfterBefore = GetFollowsAfter(stmtBefore);	// very time-consuming

		while (stmtAfterBefore != -1) {
			if (stmtAfterBefore == stmtAfter) {
				return true;
			}

			stmtBefore = stmtAfterBefore;
			stmtAfterBefore = GetFollowsAfter(stmtBefore);

		}

		return false;
	
	}

}

vector<int> Follows::GetFollowsTBefore(int stmtAfter) {
	vector<int> beforeList;

	int stmtBefore = GetFollowsBefore(stmtAfter);
	while (stmtBefore != -1) {
		beforeList.push_back(stmtBefore);

		stmtAfter = stmtBefore;
		stmtBefore = GetFollowsBefore(stmtAfter);
	
	}

	return beforeList;
}

vector<int> Follows::GetFollowsTAfter(int stmtBefore) {
	vector<int> afterList;

	int stmtAfter = GetFollowsAfter(stmtBefore);
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

int Follows::SizeOfFollows() {
	return followsTable.size();
}

/** private methods **/
bool Follows::AlreadyInserted(pair<int, int> newPair) {
	vector<pair<int, int>>::iterator newPairIterator = find(followsTable.begin(), followsTable.end(), newPair);

	return newPairIterator != followsTable.end();

}