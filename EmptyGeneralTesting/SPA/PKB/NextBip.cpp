#include "NextBip.h"
#include "Next.h"
#include "Calls.h"
#include "ProcTable.h"
#include "StmtTypeTable.h"
#include "..\Program\Program.h"

map <int, vector<int>> returnPoints; // stores points that procs return to. 
map <int, vector<int>> endsOfProcs; // stores the last next of every proc 

NextBip::NextBip() {
	ClearData();
}

void NextBip::setReturnPoint(int procedure, int returnPoint) {
	// TODO sanity checks and duplicate checks
	returnPoints[procedure].push_back(returnPoint);
}

void NextBip::setEndOfProc(int procedure, int endOfProc) {
	// TODO sanity checks and duplicate checks
	endsOfProcs[procedure].push_back(endOfProc);
}

vector<int> NextBip::GetNextAfter(int progLineBefore) {
	/*
	check for call
		if call, go to start of called proc
		else check if end of proc
			if end of proc, return return points
			else normal
	*/

	int thisProc = ProcTable::GetProcOfStmt(progLineBefore);
	vector<int> nextStmts;

	if (StmtTypeTable::CheckIfStmtOfType(progLineBefore, SynonymType::CALL)) {
		int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(progLineBefore).GetContent());
		nextStmts.push_back(ProcTable::GetFirstStmtNoOfProc(calledProc));
	} else {
		nextStmts = Next::GetNextAfter(progLineBefore);
		if (nextStmts.size() == 0) {
			for each (int callStmt in returnPoints[thisProc]) {
				vector<int> afterCall = Next::GetNextAfter(callStmt);
				if (afterCall.size() == 1) { // after Call size is only one
					nextStmts.push_back(afterCall[0]);
				}
			}
		}
	}
	return nextStmts;
}

vector<int> NextBip::GetNextBefore(int progLineAfter) {
	/*
	check for start of proc
		if start, return to call stmts (prev of return points)
	else check if previous is call
		if prev is call, return ends of procs called
		return all normal
	*/

	int thisProc = ProcTable::GetProcOfStmt(progLineAfter);
	vector<int> prevStmts = Next::GetNextBefore(progLineAfter);
	if (prevStmts.size() == 0) {
		prevStmts = returnPoints[thisProc];
	} else {
		vector<int> filteredCalls;
		for each (int stmt in prevStmts) {
			if (StmtTypeTable::CheckIfStmtOfType(stmt, SynonymType::CALL)) { // convert all prevCalls into ends of called procs
				int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(stmt).GetContent());
				vector<int> endsOfCalledProc = endsOfProcs[calledProc];
				for each (int end in endsOfCalledProc) {
					filteredCalls.push_back(end);
				}
			} else {
				filteredCalls.push_back(stmt); // normal stmt
			}
		}
		prevStmts = filteredCalls;
	}

	return prevStmts;
}


vector<int> NextBip::GetReturnTo(int terminatingStmt, int callingProc) {
	vector<int> returnPoints = GetNextAfter(terminatingStmt);
	vector<int> result;
	for each (int stmt in returnPoints) {
		if (ProcTable::GetProcOfStmt(stmt) == callingProc) {
			result.push_back(stmt);
		}
	}
	return result;
}

vector<int> NextBip::GetEntryPoint(int startingStmt, int callingProc) {
	vector<int> entryPoints = GetNextBefore(startingStmt);
	vector<int> result;
	for each (int stmt in entryPoints) {
		if (ProcTable::GetProcOfStmt(stmt) == callingProc) {
			result.push_back(stmt);
		}
	}
}

bool NextBip::IsNextT(int progLineBefore, int progLineAfter) {

}

vector<int> NextBip::GetNextTAfter(int progLineBefore) {

}

vector<int> NextBip::GetNextTBefore(int progLineAfter) {

}

void NextBip::ClearData() {
	int noOfProcs = ProcTable::GetNoOfProcs();
	vector<int> emptySet;
	for (int proc = 0; proc < noOfProcs; proc++) {
		returnPoints[proc] = emptySet;
		endsOfProcs[proc] = emptySet;
	}
}
