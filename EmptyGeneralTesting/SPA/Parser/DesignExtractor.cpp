#include "DesignExtractor.h"
#include "..\Program\Program.h"
#include "..\PKB\Follows.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\StmtTypeTable.h"
#include "..\PKB\Uses.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Calls.h"
#include "..\QueryProcessor\Grammar.h"

#include <vector>
#include <map>
#include <set>

DesignExtractor::DesignExtractor(void)
{
}

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
void ComputeModifiesAndUses();
void ComputeCalls();

void DesignExtractor::Extract() {
	ComputeModifiesAndUses();
	ComputeCalls();

}

void ComputeModifiesAndUsesForProcedures() {
	// Use calls in PKB and shrink SCCs
	// we shall use an implementation of Tarjan's strongly connected components algorithm

	struct ProcInfo {
		// check if node is visited by accessing the depth
		// check if node is in component by checking the componentIndex
		ProcInfo(int procIndex = -1) 
			: procIndex(procIndex), componentIndex(0)
			, depth(0), minReacheableDepth(-1) {}
		int procIndex;
		int componentIndex;
		int depth;
		int minReacheableDepth;
	};

	class TarjanHelper {

	public:
		TarjanHelper() {
			depthCounter, componentCounter = 0;
			// TODO find an easier way of getting this out
			for each (string procedure in ProcTable::GetAllProcNames()) {
				int procIndex = ProcTable::GetIndexOfProc(procedure);
				procMap[procIndex] = ProcInfo(procIndex);
				procedures.push_back(procIndex);
			}
		}

		map<int, ProcInfo> ComputeSCC() {
			for each (int procedure in procedures) {
				if(procMap[procedure].depth == 0) {
					Tarjan(procedure);
				}
			}
			return procMap;
		}

	private:
		map<int, ProcInfo> procMap;
		vector<int> SCCStack;
		vector<int> procedures;
		int depthCounter, componentCounter;

		void Tarjan(int proc) {
			ProcInfo& currentProcedure = procMap[proc];
			currentProcedure.depth = depthCounter;
			currentProcedure.minReacheableDepth = depthCounter;
			depthCounter++;
			SCCStack.push_back(proc);
			// map children of currentProcedure
			for each (int procedure in Calls::GetProcsCalledBy(proc)){
				ProcInfo& calledProcedure = procMap[procedure];
				if (calledProcedure.depth == 0) { // procedure has not been mapped
					Tarjan(procedure); // add proc to stack
					currentProcedure.minReacheableDepth = 
						(calledProcedure.minReacheableDepth < currentProcedure.minReacheableDepth) 
						? calledProcedure.minReacheableDepth : currentProcedure.minReacheableDepth;
				} else {
					// do not add proc to stack
					currentProcedure.minReacheableDepth = 
						(calledProcedure.minReacheableDepth < currentProcedure.minReacheableDepth) 
						? calledProcedure.minReacheableDepth : currentProcedure.minReacheableDepth;
				}
			}

			// SCC generation time
			if (currentProcedure.depth == currentProcedure.minReacheableDepth) {
				ProcInfo& nextProc = procMap[SCCStack.back()];
				while (nextProc.procIndex != currentProcedure.procIndex) {
					nextProc.componentIndex = componentCounter;
					SCCStack.pop_back();
					nextProc = procMap[SCCStack.back()];
				}
				SCCStack.pop_back();
				componentCounter++; // one component done, on to the next
			}
		}
	};

	// TODO can someone teach me to declare unnamed objects?
	TarjanHelper helper;
	map<int, ProcInfo> callGraph = helper.ComputeSCC();
	
	// iterate through procs, generating SCCs
	// for each proc, look at all procs calling said proc
	//	if the calling proc has a different component number, said proc is parent
	map<int, vector<int>> componentMap;
	map<int, bool> componentHasParent;
	map<int, set<int>> componentGraph;
	typedef map<int, ProcInfo>::iterator c_iter;
	for (c_iter i = callGraph.begin(); i != callGraph.end(); i++) {
		int procIndex = i->first;
		int componentIndex = i->second.componentIndex;
		componentMap[componentIndex].push_back(procIndex);
		// find parents
		for each (int procedure in Calls::GetProcsCalling(procIndex)) {
			int callingComponentIndex = callGraph[procedure].componentIndex;
			if (callingComponentIndex != componentIndex) {
				componentGraph[componentIndex].insert(callingComponentIndex);

			}
		}
	}

	// walk through SCC graph
	// for each vertex/component, all procs use and modify the set union of all variables in that component
	// for each child of vertex, vertex calls/modifies variables of children
	// must identify heads of graphs
	// then can have recursive implementation
	// graph guaranteed to not have loops
	typedef map<int, vector<int>>::iterator c_map_iter;
	typedef map<int, set<int>>::iterator c_grh_iter;
	// iterate through each component
	for (c_map_iter i = componentMap.begin(); i != componentMap.end(); i++) {
		// sum up the vars for all procs in the component
		for each (int procedure in i->second) {

		}
		// make all procs inherit the vars summed up
		
		// 
	}
}

void ComputeNext() {
	int numberOfStmts = Program::GetNumOfStmts();
	

}

int ConnectStmtList(int startPoint) {
	// seeks follows connections until none can be found
	// returns the last one

	return 0;
}

void ComputeCalls() {
	// inserting calls
	for each (int call in StmtTypeTable::GetAllStmtsOfType(SynonymType::CALL)) {
		TNode& callNode = Program::GetStmtFromNumber(call);
		int callingProc = ProcTable::GetProcOfStmt(call);
		int calledProc = ProcTable::GetIndexOfProc(callNode.GetContent());
		Calls::SetCalls(callingProc, calledProc);
	}
}

void ComputeModifiesAndUses() {
	// TODO migrate code
}

