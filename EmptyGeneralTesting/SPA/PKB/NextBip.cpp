#include "NextBip.h"
#include "Next.h"
#include "Calls.h"
#include "ProcTable.h"
#include "StmtTypeTable.h"
#include "..\Program\Program.h"

#include <algorithm>

// maps the called proc to the call stmts calling them
map <int, vector<int>> NextBip::returnPoints; // stores points that procs return to. 
map <int, vector<int>> NextBip::endsOfProcs; // stores the last next of every proc 

NextBip::NextBip() {
	ClearData();
}

void NextBip::setReturnPoint(int procedure, int returnPoint) {
	// TODO sanity checks and duplicate checks
	returnPoints[procedure].push_back(returnPoint);
	vector<int>::iterator it = unique(returnPoints[procedure].begin(), returnPoints[procedure].end());
	returnPoints[procedure].resize(distance(returnPoints[procedure].begin(), it));
}

void NextBip::setEndOfProc(int procedure, int endOfProc) {
	// TODO sanity checks and duplicate checks
	endsOfProcs[procedure].push_back(endOfProc);
	vector<int>::iterator it = unique(endsOfProcs[procedure].begin(), endsOfProcs[procedure].end());
	endsOfProcs[procedure].resize(distance(endsOfProcs[procedure].begin(), it));
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

	if (StmtTypeTable::CheckIfStmtOfType(progLineBefore, CALL)) {
		int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(progLineBefore).GetContent());
		nextStmts.push_back(ProcTable::GetFirstStmtNoOfProc(calledProc));
	} else {
		nextStmts = Next::GetNextAfter(progLineBefore);
		vector<int> endpts = endsOfProcs[thisProc];
		if (find(endpts.begin(), endpts.end(), progLineBefore) != endpts.end()) { // check if stmt is in endpoints
			for each (int returnPt in returnPoints[thisProc]) {
				for each (int nextStmt in Next::GetNextAfter(returnPt)) {
					nextStmts.push_back(nextStmt);
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
	if (ProcTable::GetFirstStmtNoOfProc(thisProc) == progLineAfter) {
		prevStmts.insert(prevStmts.end(), returnPoints[thisProc].begin(), returnPoints[thisProc].end());
	} else {
		vector<int> filteredCalls;
		for each (int stmt in prevStmts) {
			if (StmtTypeTable::CheckIfStmtOfType(stmt, CALL)) { // convert all prevCalls into ends of called procs
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

bool NextBip::IsNext(int progLineBefore, int progLineAfter) {
	vector<int> nextStmts = GetNextAfter(progLineBefore);
	return find(nextStmts.begin(), nextStmts.end(), progLineAfter) != nextStmts.end();
}

vector<int> NextBip::GetReturnsTo(int calledProc, int callingProc) {
	vector<int> result = vector<int>();
	for each (int stmt in GetEntryPoints(calledProc, callingProc)) {
		vector<int> afterCall = Next::GetNextAfter(stmt);
		if (afterCall.size() != 0) {
			result.insert(result.end(), afterCall.begin(), afterCall.end()); // next after call
		}
	}
	return result;
}

vector<int> NextBip::GetEntryPoints(int calledProc, int callingProc) {
	vector<int> entryPoints = returnPoints[calledProc];
	vector<int> result = vector<int>();
	for each (int stmt in entryPoints) {
		if (ProcTable::GetProcOfStmt(stmt) == callingProc) {
			result.push_back(stmt);
		}
	}
	return result;
}

vector<int> NextBip::GetAllEntryPoints(int calledProc) {
	return returnPoints[calledProc];
}

vector<int> NextBip::GetAllReturnPoints(int calledProc) {
	vector<int> result = vector<int>();
	for each (int stmt in GetAllEntryPoints(calledProc)) {
		vector<int> afterCall = Next::GetNextAfter(stmt);
		if (afterCall.size() != 0) {
			result.insert(result.end(), afterCall.begin(), afterCall.end()); // next after call
		}
	}
	return result;
}

vector<int> NextBip::GetEndPoints(int proc) {
	return endsOfProcs[proc];
}

bool NextBip::IsEndPoint(int stmt, int procedure) {
	vector<int> endpts = GetEndPoints(procedure);
	return find(endpts.begin(), endpts.end(), stmt) != endpts.end();
}

bool NextBip::IsNextBipT(int progLineBefore, int progLineAfter) {
	queue<int> linesToCheck;
	vector<int> nextAfterCurrLine;
	int maxNoOfLinesSoFar =StmtTypeTable::GetMaxStmtIndex();
	vector<bool> checkedLines (maxNoOfLinesSoFar + 1, false);
		
	int currLine;
	stack<int> enteredFrom;

	if (StmtTypeTable::CheckIfStmtOfType(progLineBefore, CALL)) {
		nextAfterCurrLine = Next::GetNextAfter(progLineBefore);
		if (!nextAfterCurrLine.empty()) {
			enteredFrom.push(nextAfterCurrLine.at(0));
		}
		int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(progLineBefore).GetContent());
		linesToCheck.push(ProcTable::GetFirstStmtNoOfProc(calledProc));
	} else {
		linesToCheck = AddToQueue(linesToCheck, Next::GetNextAfter(progLineBefore));
	}

	while (!linesToCheck.empty()) {
		currLine = linesToCheck.front();
		if (!checkedLines.at(currLine)) {
			if (currLine == progLineAfter) {
				return true;
			}

			if (StmtTypeTable::CheckIfStmtOfType(currLine, CALL)) {
				nextAfterCurrLine = Next::GetNextAfter(currLine);
				if (!nextAfterCurrLine.empty()) {
					enteredFrom.push(nextAfterCurrLine.at(0));
				}
				int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currLine).GetContent());
				linesToCheck.push(ProcTable::GetFirstStmtNoOfProc(calledProc));
			} else {
				nextAfterCurrLine = Next::GetNextAfter(currLine);
				if (nextAfterCurrLine.empty() && !enteredFrom.empty() || 
					!nextAfterCurrLine.empty() && checkedLines.at(nextAfterCurrLine.at(0))) {
					// cout << ProcTable::GetLastStmtNoOfProc(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currLine).GetContent()));
					linesToCheck.push(enteredFrom.top());
					enteredFrom.pop();
				} else {
					linesToCheck = AddToQueue(linesToCheck, Next::GetNextAfter(currLine));
				}
			}

			checkedLines[currLine] = true;

		}
		linesToCheck.pop();
	}
	return false;

}

vector<int> NextBip::GetNextBipTAfter(int progLineBefore) {
	queue<int> linesToCheck;
	vector<int> linesAfter, nextAfterCurrLine;
	vector<bool> checkedLines (StmtTypeTable::GetMaxStmtIndex() + 1, false);
	
	int currLine;
	stack<int> enteredFrom;

	if (StmtTypeTable::CheckIfStmtOfType(progLineBefore, CALL)) {
		nextAfterCurrLine = Next::GetNextAfter(progLineBefore);
		if (!nextAfterCurrLine.empty()) {
			enteredFrom.push(nextAfterCurrLine.at(0));
		}
		int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(progLineBefore).GetContent());
		linesToCheck.push(ProcTable::GetFirstStmtNoOfProc(calledProc));
	} else {
		linesToCheck = AddToQueue(linesToCheck, Next::GetNextAfter(progLineBefore));
	}

	while (!linesToCheck.empty()){
		currLine = linesToCheck.front();
		if (!checkedLines.at(currLine)) {		// in case of while loops
			linesAfter.push_back(currLine);
			if (StmtTypeTable::CheckIfStmtOfType(currLine, CALL)) {
				nextAfterCurrLine = Next::GetNextAfter(currLine);
				if (!nextAfterCurrLine.empty()) {
					enteredFrom.push(nextAfterCurrLine.at(0));
				}
				int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currLine).GetContent());
				linesToCheck.push(ProcTable::GetFirstStmtNoOfProc(calledProc));
			} else {
				nextAfterCurrLine = Next::GetNextAfter(currLine);
				if (nextAfterCurrLine.empty() && !enteredFrom.empty() || 
					!nextAfterCurrLine.empty() && checkedLines.at(nextAfterCurrLine.at(0))) {
					// cout << ProcTable::GetLastStmtNoOfProc(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currLine).GetContent()));
					linesToCheck.push(enteredFrom.top());
					enteredFrom.pop();
				} else {
					linesToCheck = AddToQueue(linesToCheck, Next::GetNextAfter(currLine));
				}
			}
			checkedLines[currLine] = true;

		}
		linesToCheck.pop();

	}

	return linesAfter;

}

vector<int> NextBip::GetNextBipTBefore(int progLineAfter) {
	queue<int> linesToCheck;
	vector<int> linesBefore, nextBeforeCurrLine;
	vector<bool> checkedLines (StmtTypeTable::GetMaxStmtIndex() + 1, false);
	
	int currLine;
	stack<int> enteredFrom;

	int thisProc = ProcTable::GetProcOfStmt(progLineAfter);
	
	nextBeforeCurrLine = Next::GetNextBefore(progLineAfter);
	if (nextBeforeCurrLine.empty()) {
		linesToCheck = AddToQueue(linesToCheck, returnPoints[thisProc]);
	} else {
		linesToCheck = AddToQueue(linesToCheck, nextBeforeCurrLine);
	}
	
	while (!linesToCheck.empty()){
		currLine = linesToCheck.front();
		//cout << "\ncurrLine: " << currLine << " ";
		if (!checkedLines.at(currLine)) {
			linesBefore.push_back(currLine);
			int thisProc = ProcTable::GetProcOfStmt(currLine);
			if (StmtTypeTable::CheckIfStmtOfType(currLine, CALL)) {
				enteredFrom.push(currLine);
				int calledProc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currLine).GetContent());
				nextBeforeCurrLine = endsOfProcs[calledProc];
				linesToCheck = AddToQueue(linesToCheck, nextBeforeCurrLine);
			} else if (currLine == ProcTable::GetFirstStmtNoOfProc(thisProc)) {
				//cout << "\n\t reached the top!";
				if (enteredFrom.empty()) {
					//cout << "\n no calling procedure";
					nextBeforeCurrLine = returnPoints[thisProc];
					for (vector<int>::iterator it = nextBeforeCurrLine.begin(); it != nextBeforeCurrLine.end(); it++) {
						linesToCheck.push(*it);
						linesBefore.push_back(*it);
						checkedLines[*it] = true;
					}
					//linesToCheck = AddToQueue(linesToCheck, nextBeforeCurrLine);
				} else {
					//cout << "\n called by: " << enteredFrom.top() << " ";
					linesToCheck.push(enteredFrom.top());
					enteredFrom.pop();
				}
			} else {
				//cout << "\n next before this is: " << Next::GetNextBefore(currLine).at(0) << " ";
				linesToCheck = AddToQueue(linesToCheck, Next::GetNextBefore(currLine));
			}

			checkedLines[currLine] = true;
		} else {
			if (StmtTypeTable::CheckIfStmtOfType(currLine, CALL)) {
				linesToCheck = AddToQueue(linesToCheck, Next::GetNextBefore(currLine));
			}
		}
		linesToCheck.pop();
	}
	return linesBefore;

}

void NextBip::ClearData() {
	int noOfProcs = ProcTable::GetNoOfProcs();
	vector<int> emptySet;
	for (int proc = 0; proc < noOfProcs; proc++) {
		returnPoints[proc] = emptySet;
		endsOfProcs[proc] = emptySet;
	}
}

queue<int> NextBip::AddToQueue(queue<int> linesToCheck, vector<int> additions) {
	for (vector<int>::iterator it = additions.begin(); it != additions.end(); it++) {
		linesToCheck.push(*it);
	}

	return linesToCheck;

}