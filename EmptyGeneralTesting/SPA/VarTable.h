#include<stdio.h>
#include<string>
#include<set>

using namespace std;

class VarTable {
public:
	// Default constructor
	VarTable();

	// Methods
	int insertVar(string varName);
	int getIndexOf(string varName); 
	string getVarName(int varIndex);
	int getSize();

private:
	set<string>  varNames;	// List of variable strings
	// insert subsequent columns of the VarTable here

};