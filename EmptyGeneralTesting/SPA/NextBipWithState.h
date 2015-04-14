#pragma once

#include <vector>
#include <deque>

using namespace std;

class NextBipWithState {
public:
	NextBipWithState(deque<int> callStack = deque<int>());

	static vector<int> GetNextAfter(int progLineBefore);
	static vector<int> GetNextBefore(int progLineAfter);

	static void ResetState();

private:
	static deque<int> ProcCallStack;
};

