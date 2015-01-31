#pragma once

#include <vector>
#include <algorithm>
#include "ProcTable.h"
#include "..\Exception\IndexNotFoundException.h"

using namespace std;

vector<string>  ProcTable::procNames;
vector<int> ProcTable::firstStmtNo;
vector<int> ProcTable::lastStmtNo;

// empty constructor
ProcTable::ProcTable() {}

// API
int ProcTable::InsertProc(string procName) {
	vector<string>::iterator searchResult = SearchFor(procName);

	if (searchResult != procNames.end()) {
		return distance(procNames.begin(), searchResult);

	} else {
		procNames.push_back(procName);
		return procNames.size() - 1;

	}
}

int ProcTable::GetIndexOfProc(string procName) {
	vector<string>::iterator searchResult = SearchFor(procName);

	if (searchResult != procNames.end()) {
		return distance(procNames.begin(), searchResult);

	} else {
		return -1;

	}

}

string ProcTable::GetProcName(int procIndex) {
	if (procIndex >= 0 && (unsigned int)procIndex < procNames.size()) {
		return procNames[procIndex];
	} else {
		throw IndexNotFoundException();
	}

}

vector<string> ProcTable::GetAllProcNames() {
	return procNames;
}

int ProcTable::getFirstStmtNoOfProc(int procIndex) {
	return firstStmtNo.at(procIndex);
}

int ProcTable::getLastStmtNoOfProc(int procIndex) {
	return lastStmtNo.at(procIndex);
}

// methods to aid testing
int ProcTable::GetSize() {
	return procNames.size();

}

void ProcTable::ClearData() {
	procNames.clear();

}

/*Private Methods*/
vector<string>::iterator ProcTable::SearchFor(string procName) {
	return find(procNames.begin(), procNames.end(), procName);

}