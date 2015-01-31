#pragma once

#include<string>
#include<vector>

using namespace std;

/** to store a mapping of all processes, and
	- their indexes
	- the stmts they contain **/

class ProcTable {
public:
	// methods
	// Default constructor
	ProcTable();

	// Methods
	static int InsertProc(string procName);
	static int GetIndexOfProc(string procName); 
	static string GetProcName(int varIndex);
	static vector<string> GetAllProcNames();
	static int getFirstStmtNoOfProc(int procIndex);
	static int getLastStmtNoOfProc(int procIndex);
	
	// methods to aid testing
	static int GetSize();
	static void ClearData();

private:
	static vector<string>  procNames;
	static vector<int> firstStmtNo;
	static vector<int> lastStmtNo;

	static vector<string>::iterator SearchFor(string procName);

};
