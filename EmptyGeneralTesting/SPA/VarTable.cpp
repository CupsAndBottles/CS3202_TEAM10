#include "VarTable.h"
#include <algorithm>

// Default constructor
VarTable::VarTable() {
	// empty constructor
}

// Methods
int VarTable::insertVar(string varName) {
	pair<set<string>::iterator, bool> insertResultPair = varNames.insert(varName);
	set<string>::iterator varIndex = insertResultPair.first;
	bool varExists = insertResultPair.second;

	return distance(varNames.begin(), insertResultPair.first);

}

int VarTable::getIndexOf(string varName) {
	set<string>::iterator searchResult = varNames.find(varName);

	if (searchResult != varNames.end()) {
		return distance(varNames.begin(), searchResult);

	} else {
		return -1;

	}

}

string VarTable::getVarName(int varIndex) {
	set<string>::iterator varNamesIterator = varNames.begin(); 

	// if varIndex is out of range, throw exception

	for (int i = 0; i < varIndex; i++) {
		varNamesIterator++;
	}

	return *varNamesIterator;

}

int VarTable::getSize() {
	return varNames.size();

}