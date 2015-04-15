#include "DesignExtractor.h"
#include "..\Program\Program.h"
#include "..\PKB\Follows.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\StmtTypeTable.h"
#include "..\PKB\Uses.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Calls.h"
#include "..\PKB\Next.h"
#include "..\PKB\Parent.h"
#include "..\PKB\NextBip.h"
#include "..\PKB\NodeTypeTable.h"
#include "..\QueryProcessor\Grammar.h"

#include <vector>
#include <map>
#include <set>

/*
proctable
	first and last stmts of each procedure
Modifies/Uses
	Move code for recursive calls from PKB to here.
calls
	get calls stmts from stmttypetable
	get procedures containing said stmts from proctable
	build call tree.
procedure - modifies/uses
	Build call tree
	reduce SCCs to vertices
	compile uses and modifies for resulting graph
Next
	use follows to calculate
	return tail of next chain
		start on stmt 1
			when encountering a while loop
				perform recursive call to parse subtree
				connect tail to head, proceed.
			when encountering if/then/else block
				perform recursive call to parse subtrees
				connect tails to follows(ifstmt, next)
*/

void ComputeNodeTypeTable();
void ComputeModifiesAndUses();
void ComputeCalls();
void ComputeModifiesAndUsesForProcedures();
void ComputeNext();
void ComputeNextBip();

void DesignExtractor::Extract() {
	ComputeNodeTypeTable();
	ComputeCalls();
	ComputeNext();
	ComputeNextBip();
	ComputeModifiesAndUsesForProcedures();
	ComputeModifiesAndUses();
}

void ComputeNodeTypeTable() {
	// flatten nodes and iterate through them
	// ast has no loops if following only child links.

	NodeTypeTable::Initialise();
	
	vector<TNode*> currentSet;
	currentSet.push_back(&Program::GetASTRootNode());

	while (currentSet.size() > 0) {
		vector<TNode*> nextSet;
		for each (TNode* nodeptr in currentSet) {
			NodeTypeTable::Insert(nodeptr);
			for each (TNode* child in nodeptr->GetChildren()) {
				nextSet.push_back(child);
			}
		}
		currentSet = nextSet;
	}
}

void ComputeModifiesAndUsesForProcedures() {
	/* 
	find all procedures that are not called by other procedures
	for all said procedures, recursively add properties of children to procedure
	*/

	vector<int> procIndexes = vector<int>();
	for each (string procName in ProcTable::GetAllProcNames()) {
		procIndexes.push_back(ProcTable::GetIndexOfProc(procName));
	}

	vector<int> rootProcs = vector<int>();
	for each (int proc in procIndexes) {
		if (Calls::GetProcsCalling(proc).size() == 0) { // guaranteed to have at least one, because there are no loops
			rootProcs.push_back(proc);
		}
	}
}

set<int> ConnectStmtList(int startPoint) {
	// seeks follows connections until none can be found
	// if while is found
	//	recursively call this to process the stmt list
	//	connect last stmt to first one
	// if else is found
	//	recursively call this twice for each stmt list
	//	connect last stmts to next one
	// return last stmt found (or a set)

	set<int> prevStmts;
	int currentStmt = startPoint;
	while (currentStmt != -1) {
		// set connections
		for each (int prevStmt in prevStmts) Next::SetNext(prevStmt, currentStmt);
		prevStmts.clear();
		// process current stmt
		if (StmtTypeTable::CheckIfStmtOfType(currentStmt, IF)) {

			TNode& ifStmt = Program::GetStmtFromNumber(currentStmt);
			int startOfThenBlock = ifStmt.GetChild(1).GetChild(0).GetLineNumber();
			int startOfElseBlock = ifStmt.GetChild(2).GetChild(0).GetLineNumber();
			Next::SetNext(currentStmt, startOfThenBlock);
			Next::SetNext(currentStmt, startOfElseBlock);

			set<int> thenBlockEnds = ConnectStmtList(startOfThenBlock);
			set<int> elseBlockEnds = ConnectStmtList(startOfElseBlock);
			prevStmts.insert(thenBlockEnds.begin(), thenBlockEnds.end());
			prevStmts.insert(elseBlockEnds.begin(), elseBlockEnds.end());

		} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, WHILE)) {

			TNode& whileStmt = Program::GetStmtFromNumber(currentStmt);
			int startOfLoop = whileStmt.GetChild(1).GetChild(0).GetLineNumber();
			Next::SetNext(currentStmt, startOfLoop);
			
			set<int> loopEnds = ConnectStmtList(startOfLoop);
			for each (int stmt in loopEnds) Next::SetNext(stmt, currentStmt);
			prevStmts.insert(currentStmt);

		} else {
			prevStmts.insert(currentStmt);
		}
		// goto next stmt
		currentStmt = Follows::GetFollowsAfter(currentStmt);
	}
	return prevStmts;
}

void ComputeNext() {
	// gets all procedures
	// loops through all procedures, connecting the stmts
	for each (string procName in ProcTable::GetAllProcNames()) {
		int procIndex = ProcTable::GetIndexOfProc(procName);
		set<int> finalStmts = ConnectStmtList(ProcTable::GetFirstStmtNoOfProc(procIndex));
		for each (int stmt in finalStmts) {
			NextBip::setEndOfProc(procIndex, stmt);
		}
	}
}

void ComputeCalls() {
	// inserting calls
	for each (int call in StmtTypeTable::GetAllStmtsOfType(CALL)) {
		TNode& callNode = Program::GetStmtFromNumber(call);
		int callingProc = ProcTable::GetProcOfStmt(call);
		int calledProc = ProcTable::GetIndexOfProc(callNode.GetContent());
		Calls::SetCalls(callingProc, calledProc);
	}
}

void ComputeModifiesAndUses() {
	/* Remember that
		while x {		\\ 1
			while y {	\\ 2
				z = 1;	\\ 3
			}
		}

		1 only modifies 3, and not 2 as well.
	*/

	// get all assignment statements
	// map to direct parents
	// direct parents inherit properties of children
	// set direct parents as new children
	// loop

	vector<int> assignmentStmts = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
	vector<int> callStmts = StmtTypeTable::GetAllStmtsOfType(CALL);

	set<int> currentChildren;
	currentChildren.insert(assignmentStmts.begin(), assignmentStmts.end());
	currentChildren.insert(callStmts.begin(), callStmts.end());
	
	while (currentChildren.size() != 0) {
		set<int> parents;

		for each (int stmt in currentChildren) {
			int parent = Parent::GetParentOf(stmt);
			if (parent == -1) continue;
			vector<int> usedVars, modifiedVars;

			if (StmtTypeTable::GetStmtTypeOf(stmt) == CALL) {
				// should only encounter this code on the first pass. Maybe can optimise
				int proc = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(stmt).GetContent());
				usedVars = Uses::GetVarUsedByProc(proc);
				// compute modifies and uses for calls here as well
				modifiedVars = Modifies::GetVarModifiedByProc(proc);
				for each (int var in usedVars) {
					Uses::SetStmtUsesVar(stmt, var);
				}
				for each (int var in modifiedVars) {
					Modifies::SetStmtModifiesVar(stmt, var);
				}
			} else { // assign or while or whatever
				usedVars = Uses::GetVarUsedByStmt(stmt);
				modifiedVars = Modifies::GetVarModifiedByStmt(stmt);
			}

			for each (int var in usedVars) {
				Uses::SetStmtUsesVar(parent, var);
			}
			for each (int var in modifiedVars) {
				Modifies::SetStmtModifiesVar(parent, var);
			}
			parents.insert(parent);
		}

		currentChildren = parents;
	}
}

void ComputeNextBip() {
	for each (int call in StmtTypeTable::GetAllStmtsOfType(CALL)) {
		TNode& callNode = Program::GetStmtFromNumber(call);
		int calledProc = ProcTable::GetIndexOfProc(callNode.GetContent());
		NextBip::setReturnPoint(calledProc, call);
	}

}