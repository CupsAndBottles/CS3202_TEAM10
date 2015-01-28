#pragma once

#include "VarTable.h"
#include "..\Exception\IndexNotFoundException.h"
#include <algorithm>
#include <vector>

 vector<string>  VarTable::varNames;

/* Public Methods*/
unsigned int VarTable::InsertVar(string varName) {
	vector<string>::iterator searchResult = SearchFor(varName);

	if (searchResult != varNames.end()) {
		return distance(varNames.begin(), searchResult);

	} else {
		varNames.push_back(varName);
		return varNames.size() - 1;

	}

}

unsigned int VarTable::GetIndexOf(string varName) {
	vector<string>::iterator searchResult = SearchFor(varName);

	if (searchResult != varNames.end()) {
		return distance(varNames.begin(), searchResult);

	} else {
		return -1;

	}

}

string VarTable::GetVarName(unsigned int varIndex) {
	if (varIndex >= 0 && varIndex < varNames.size()) {
		return varNames[varIndex];
	} else {
		throw IndexNotFoundException();
	}

}

// methods to aid testing
unsigned int VarTable::GetSize() {
	return varNames.size();

}

void VarTable::ClearData() {
	varNames.clear();

}

/*Private Methods*/
vector<string>::iterator VarTable::SearchFor(string varName) {
	return find(varNames.begin(), varNames.end(), varName);

}

vector<string> VarTable::GetAllVar() {
	return varNames;
}