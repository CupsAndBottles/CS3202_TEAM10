#pragma once

//#include<stdio.h>
#include<string>
#include<vector>

using namespace std;


/** To store a mapping of all variables
	and their indexes. **/

class VarTable {
public:
	// Default constructor
	VarTable();

	// Methods
	static unsigned int InsertVar(string varName);
	static unsigned int GetIndexOf(string varName); 
	static string GetVarName(unsigned int varIndex);
	static vector<string> GetAllVar();
	
	// methods to aid testing
	static unsigned int GetSize();
	static void ClearData();

private:
	static vector<string>  varNames;	// List of variable strings
	// insert subsequent columns of the VarTable here

	static vector<string>::iterator SearchFor(string varName);

};