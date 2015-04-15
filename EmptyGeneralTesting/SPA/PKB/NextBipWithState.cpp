#include "NextBipWithState.h"
#include "Next.h"
#include "NextBip.h"
#include "Calls.h"
#include "ProcTable.h"
#include "StmtTypeTable.h"
#include "..\Program\Program.h"

NextBipWithState::NextBipWithState(int startStmt, deque<int> callStack) : currentStmt(startStmt) {
	currentProc = ProcTable::GetProcOfStmt(startStmt);
	procCallStack = callStack;
}

vector<NextBipWithState> NextBipWithState::GoNext() {
	vector<NextBipWithState> nextBips;

	if (StmtTypeTable::CheckIfStmtOfType(currentStmt, CALL)) {
		int nextStmt = NextBip::GetNextAfter(currentStmt)[0]; // guaranteed to only be one.
		procCallStack.push_back(currentStmt);
		nextBips.push_back(NextBipWithState(nextStmt, procCallStack));
	} else {
		// check for end of proc
		if (NextBip::IsEndPoint(currentStmt, currentProc)) {
			if (LengthOfCallChain() > 0) {
				// return from call
				int returnPoint = Next::GetNextAfter(procCallStack.back())[0];
				deque<int> resultantCallStack = procCallStack; resultantCallStack.pop_back();
				nextBips.push_back(NextBipWithState(returnPoint, resultantCallStack));
			} else {
				// no call, so return to all calls
				vector<int> returnPoints = NextBip::GetAllReturnPoints(currentProc);
				for each (int stmt in returnPoints) {
					nextBips.push_back(NextBipWithState(stmt)); // reset all state for returns
				}
			}
		}

		// normal next
		vector<int> nextStmts = Next::GetNextAfter(currentStmt);
		for each (int stmt in nextStmts) {
			nextBips.push_back(NextBipWithState(stmt, procCallStack));
		}
	}
	return nextBips;
}

int NextBipWithState::LengthOfCallChain() {
	return procCallStack.size();
}

vector<NextBipWithState> NextBipWithState::GoPrev() {
	vector<NextBipWithState> prevBips;

	if (ProcTable::GetFirstStmtNoOfProc(currentProc) == currentStmt) {
		if (LengthOfCallChain() > 0) {
			// just assume there is state
			int entryPoint = procCallStack.back();
			deque<int> resultantCallStack = procCallStack; resultantCallStack.pop_back();
			prevBips.push_back(NextBipWithState(entryPoint, resultantCallStack));
		}

		for each (int previous in Next::GetNextBefore(currentStmt)) { // normal previous
			prevBips.push_back(NextBipWithState(previous, procCallStack));
		}
	} else { // not start, so normal previous and check for calls
		vector<int> prevStmts = Next::GetNextBefore(currentStmt);
		for each (int stmt in prevStmts) {
			if (StmtTypeTable::CheckIfStmtOfType(stmt, CALL)) { // convert all prevCalls into ends of called procs
				// return into reverse call
				int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(stmt).GetContent());
				vector<int> endsOfCalledProc = NextBip::GetEndPoints(calledProc);
				deque<int> resultantCallStack = procCallStack; resultantCallStack.push_back(stmt);
				for each (int end in endsOfCalledProc) {
					prevBips.push_back(NextBipWithState(end, resultantCallStack));
				}
			} else {
				prevBips.push_back(NextBipWithState(stmt, procCallStack)); // normal stmt
			}
		}
	}

	return prevBips;

}

