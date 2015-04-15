#pragma once

#include <vector>
#include <deque>

using namespace std;

class NextBipWithState {
public:
	NextBipWithState(int startStmt, deque<int> callStack = deque<int>());

	vector<NextBipWithState> GoNext();
	vector<NextBipWithState> GoPrev();

	int LengthOfCallChain();

	int GetCurrentStmt();

private:
	// call stack stores call stmts that directed the flow
	deque<int> procCallStack;
	int currentStmt;
	int currentProc;
};

