#include "Follows.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

vector<pair<unsigned int, unsigned int>> Follows::followsTable;

/** public methods **/
// Default constructor
Follows::Follows() {
	// empty constructor
}

// Methods
void Follows::SetFollows(unsigned int stmtBefore, unsigned int stmtAfter) {
	pair<unsigned int, unsigned int> newFollowsRelationship(stmtBefore, stmtAfter);
	
	if (!AlreadyInserted(newFollowsRelationship)) {
		followsTable.push_back(newFollowsRelationship);

	}

	// next time check also that no 2 stmts have >1 follows before and >1 follows after

}

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

	}

	return -1;

}

unsigned int Follows::GetFollowsAfter(unsigned int stmtBefore) {
	pair<unsigned int, unsigned int> checkFollowsRelationship;

	// sequential search for now
	for (unsigned unsigned int i = 0; i < followsTable.size(); i++) {
		checkFollowsRelationship = followsTable.at(i);

		if (checkFollowsRelationship.first == stmtBefore) {
			return checkFollowsRelationship.second;
		
		}

	}

	return -1;

}

bool Follows::IsFollowsT(unsigned int stmtBefore, unsigned int stmtAfter) {
	if (IsFollows(stmtBefore, stmtAfter)) {
		return true;

	} else {
		unsigned int stmtAfterBefore = GetFollowsAfter(stmtBefore);	// very time-consuming

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

vector<unsigned int> Follows::GetFollowsTBefore(unsigned int stmtAfter) {
	vector<unsigned int> beforeList;

	unsigned int stmtBefore = GetFollowsBefore(stmtAfter);
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

unsigned int Follows::SizeOfFollows() {
	return followsTable.size();
}

/** private methods **/
bool Follows::AlreadyInserted(pair<unsigned int, unsigned int> newPair) {
	vector<pair<unsigned int, unsigned int>>::iterator newPairIterator = find(followsTable.begin(), followsTable.end(), newPair);

	return newPairIterator != followsTable.end();

}

void Follows::ClearData() {
	followsTable.clear();

}