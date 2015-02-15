#include <algorithm>
#include <utility>
#include <map>
#include <vector>

#include "Next.h"

map <int, int> Next::beforeToAfterTable;
map <int, int> Next::afterToBeforeTable;

/** public methods **/
Next::Next() {
	// empty constructor
}

// Methods
void Next::SetNext(int stmtBefore, int stmtAfter) {
	if (NoRelationshipConflicts(stmtBefore, stmtAfter)) {
		beforeToAfterTable[stmtBefore] = stmtAfter;
		afterToBeforeTable[stmtAfter] = stmtBefore;

	}

}

bool Next::IsNext(int stmtBefore, int stmtAfter) {
	return beforeToAfterTable[stmtBefore] == stmtAfter;

}

int Next::GetNextBefore(int stmtAfter) {
	if(!HasNoStmtBefore(stmtAfter)) {
		return afterToBeforeTable[stmtAfter];

	} else {
		return -1;

	}

}

int Next::GetNextAfter(int stmtBefore) {
	if(!HasNoStmtAfter(stmtBefore)) {
		return beforeToAfterTable[stmtBefore];

	} else {
		return -1;

	}

}

bool Next::IsNextT(int stmtBefore, int stmtAfter) {
	int currBefore = stmtBefore;

	while (!HasNoStmtAfter(currBefore)) {
		if (beforeToAfterTable[currBefore] == stmtAfter) {
			return true;

		}

		currBefore = beforeToAfterTable[currBefore];
	
	}

	return false;

}

vector<int> Next::GetNextTBefore(int stmtAfter) {
	vector<int> beforeList;
	int stmtBefore = GetNextBefore(stmtAfter);

	while (stmtBefore != -1) {
		beforeList.push_back(stmtBefore);

		stmtAfter = stmtBefore;
		stmtBefore = GetNextBefore(stmtAfter);
	
	}

	return beforeList;
}

vector<int> Next::GetNextTAfter(int stmtBefore) {
	vector<int> afterList;

	int stmtAfter = GetNextAfter(stmtBefore);
	while (stmtAfter != -1) {
		afterList.push_back(stmtAfter);

		stmtBefore = stmtAfter;
		stmtAfter = GetNextAfter(stmtBefore);
	
	}


	return afterList;
}

bool Next::HasAnyFollows() {
	return SizeOfNext() > 0;
}

int Next::SizeOfNext() {
	return beforeToAfterTable.size();
}

void Next::ClearData() {
	beforeToAfterTable.clear();
	afterToBeforeTable.clear();
}

/** private methods **/
bool Next::NoRelationshipConflicts(int stmtBefore, int stmtAfter) {
	return HasNoStmtAfter(stmtBefore) && HasNoStmtBefore(stmtAfter);

}

bool Next::HasNoStmtAfter(int stmtBefore) {
	return beforeToAfterTable.find(stmtBefore) == beforeToAfterTable.end();
}

bool Next::HasNoStmtBefore(int stmtAfter) {
	return afterToBeforeTable.find(stmtAfter) == afterToBeforeTable.end();
}