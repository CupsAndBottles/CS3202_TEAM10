#pragma once

#include "VarTable.h"
#include "Exception\IndexNotFoundException.h"
#include <algorithm>
#include <vector>

// Default constructor
VarTable::VarTable() {
	// empty constructor
}

// Method

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
	if (varIndex >= 0 && varIndex < varNames.size()) {
		return varNames[varIndex];
	} else {
		throw IndexNotFoundException();
	}

}

int VarTable::GetSize() {
	return varNames.size();

}

vector<string>::iterator VarTable::SearchFor(string varName) {
	return find(varNames.begin(), varNames.end(), varName);

}

void VarTable::ClearData() {
	varNames.clear();

}