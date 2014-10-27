#include "VarTable.h"
#include <utility>
#include <algorithm>

// Default constructor
VarTable::VarTable() {
	// empty constructor
}

// Methods
int VarTable::InsertVar(string varName) {
	vector<string>::iterator searchResult = SearchFor(varName);

	if (searchResult != varNames.end()) {
		return distance(varNames.begin(), searchResult);

	} else {
		varNames.push_back(varName);
		return varNames.size() - 1;

	}

}

int VarTable::GetIndexOf(string varName) {
	vector<string>::iterator searchResult = SearchFor(varName);

	if (searchResult != varNames.end()) {
		return distance(varNames.begin(), searchResult);

	} else {
		return -1;

	}

}

string VarTable::GetVarName(int varIndex) {
	// if varIndex is out of range, throw exception
	// else
	return varNames[varIndex];

}

int VarTable::GetSize() {
	return varNames.size();

}

vector<string>::iterator VarTable::SearchFor(string varName) {
	return find(varNames.begin(), varNames.end(), varName);

}