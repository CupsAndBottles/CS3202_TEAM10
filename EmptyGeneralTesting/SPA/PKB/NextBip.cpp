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
	returnPoints[procedure].push_back(returnPoint);
}

void NextBip::setEndOfProc(int procedure, int endOfProc) {
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
			int thisProc = ProcTable::GetProcOfStmt(progLineBefore);
			return returnPoints[thisProc];
		}
	}

	return nextStmts;
}

vector<int> NextBip::GetNextBefore(int progLineAfter) {
	/*
	check for start of proc
		if start, return to call stmts
	else check if previous is call
		if prev is call, return ends of procs called
		return all normal
	*/
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
