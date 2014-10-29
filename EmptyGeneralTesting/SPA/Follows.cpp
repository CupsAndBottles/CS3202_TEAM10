#include "Follows.h"
#include <algorithm>
#include <utility>
#include <vector>

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

}

bool Follows::IsFollows (int stmtBefore, int stmtAfter) {
	pair<int, int> newFollowsRelationship(stmtBefore, stmtAfter);

	return AlreadyInserted(newFollowsRelationship);

}

int Follows::GetFollowsBefore(int stmtAfter) {
	return -123;
}

int Follows::GetFollowsAfter(int stmtBefore) {
	return -123;
}

bool Follows::AlreadyInserted(pair<int, int> newPair) {
	vector<pair<int, int>>::iterator newPairIterator = find(followsTable.begin(), followsTable.end(), newPair);

	return newPairIterator != followsTable.end();

}