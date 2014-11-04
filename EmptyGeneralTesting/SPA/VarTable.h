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
	int InsertVar(string varName);
	static int GetIndexOf(string varName); 
	static string GetVarName(int varIndex);
	static int GetSize();

private:
	vector<string>  varNames;	// List of variable strings
	// insert subsequent columns of the VarTable here

	vector<string>::iterator SearchFor(string varName);

};