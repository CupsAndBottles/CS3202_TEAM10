#include <map>
#include <vector>
#include <queue>

#include "Calls.h"
#include "ProcTable.h"

map<int, vector<int>> Calls::callingToCalledTable;
map<int, vector<int>> Calls::calledToCallingTable;
map<int, vector<bool>> Calls::callingToCalledBitVector;
int Calls::noOfCallsRelationships;
int Calls::maxNoOfProcs;
bool Calls::bitVectorIsBuilt;

// empty constructor
Calls::Calls() {
	noOfCallsRelationships = 0;
	maxNoOfProcs = 0;
	bitVectorIsBuilt = false;
}

// API
void Calls::SetCalls(int procCalling, int procCalled) {
	if (!IsCalls(procCalling, procCalled)  && !IsCalls(procCalled, procCalling)) {
		callingToCalledTable[procCalling].push_back(procCalled);
		calledToCallingTable[procCalled].push_back(procCalling);

		SetCallingToCalledBitVector(procCalling, procCalled);

		noOfCallsRelationships++;

		maxNoOfProcs = maxNoOfProcs > procCalling ? maxNoOfProcs : procCalling;
		maxNoOfProcs = maxNoOfProcs > procCalled ? maxNoOfProcs : procCalled;

	}

}

void Calls::SetCallingToCalledBitVector(int procCalling, int procCalled) {
	if ((procCalled + 1) > (int) callingToCalledBitVector[procCalling].size()) {
		for (int i = 0; i < ((procCalled + 1) * 2); i++) {
			callingToCalledBitVector[procCalling].push_back(false);
		}
	}

	callingToCalledBitVector[procCalling].at(procCalled) = true;

}

bool Calls::IsCalls(int stmtCalling, int procCalled) {
	if (callingToCalledBitVector.count(stmtCalling) != 0) {
		if ((procCalled + 1) <= (int) callingToCalledBitVector[stmtCalling].size())
			return callingToCalledBitVector[stmtCalling].at(procCalled);
	}

	return false;
}

vector<int> Calls::GetProcsCalledBy(int procCalling) {
	if(callingToCalledTable.count(procCalling) != 0) {
		return callingToCalledTable[procCalling];
	} else {
		vector<int> emptyVector;
		return emptyVector;
	}
}

vector<int> Calls::GetProcsCalling(int procCalled) {
	if(calledToCallingTable.count(procCalled) != 0) {
		return calledToCallingTable[procCalled];
	} else {
		vector<int> emptyVector;
		return emptyVector;
	}
}

bool Calls::IsCallsT(int procCalling, int procCalled) {
	if(bitVectorIsBuilt) {
		// not implemented yet
		return false; //dummy value
	} else {
		queue<int> procsToCheck;
		
		int maxNoOfProcsSoFar = maxNoOfProcs > ProcTable::GetSize() ? maxNoOfProcs : ProcTable::GetSize();
		vector<bool> checkedProcs (maxNoOfProcsSoFar + 1, false);
		
		int currProc;

		procsToCheck.push(procCalling);

		while (!procsToCheck.empty()) {
			currProc = procsToCheck.front();

			if (!checkedProcs.at(currProc)) {
				if (IsCalls(currProc, procCalled)) {
					return true;
				}

				checkedProcs[currProc] = true;
				procsToCheck = AddToQueue(procsToCheck, GetProcsCalledBy(currProc));

			}

			procsToCheck.pop();
	
		}

		return false;
	}

}

vector<int> Calls::GetProcsCalledTBy(int procCalling) {
	queue<int> procsToCheck;
	vector<int> procsCalledTBy;
	
	int maxNoOfProcsSoFar = maxNoOfProcs > ProcTable::GetSize() ? maxNoOfProcs : ProcTable::GetSize();
	vector<bool> checkedProcs (maxNoOfProcsSoFar + 1, false);

	int currProc;

	procsToCheck = AddToQueue(procsToCheck, GetProcsCalledBy(procCalling));

	while (!procsToCheck.empty()) {
		currProc = procsToCheck.front();
		if (!checkedProcs.at(currProc)) {
			procsCalledTBy.push_back(currProc);
			procsToCheck = AddToQueue(procsToCheck, GetProcsCalledBy(currProc));

			checkedProcs[currProc] = true;
		}
		procsToCheck.pop();
	
	}

	return procsCalledTBy;

}

vector<int> Calls::GetProcsCallingT(int procCalled) {
	queue<int> procsToCheck;
	vector<int> procsCallingT;
	
	int maxNoOfProcsSoFar = maxNoOfProcs > ProcTable::GetSize() ? maxNoOfProcs : ProcTable::GetSize();
	vector<bool> checkedProcs (maxNoOfProcsSoFar + 1, false);
	
	int currProc;

	procsToCheck = AddToQueue(procsToCheck, GetProcsCalling(procCalled));

	while (!procsToCheck.empty()) {
		currProc = procsToCheck.front();
		if(!checkedProcs.at(currProc)) {
			procsCallingT.push_back(currProc);
			procsToCheck = AddToQueue(procsToCheck, GetProcsCalling(currProc));

			checkedProcs[currProc] = true;
		}
		procsToCheck.pop();

	}

	return procsCallingT;
}

queue<int> Calls::AddToQueue(queue<int> procsToCheck, vector<int> additions) {
	for (unsigned int i = 0; i < additions.size(); i++) {
		procsToCheck.push(additions.at(i));
	}

	return procsToCheck;

}

bool Calls::HasAnyCalls() {
	return noOfCallsRelationships > 0;
}

int Calls::SizeOfCalls() {
	return noOfCallsRelationships;
}

void Calls::ClearData() {
	callingToCalledTable.clear();
	calledToCallingTable.clear();
	callingToCalledBitVector.clear();
	noOfCallsRelationships = 0;
}