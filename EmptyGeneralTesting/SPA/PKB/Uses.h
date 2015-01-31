#ifndef USES_H
#define USES_H

#include <utility>
#include <vector>
#include <map>

using namespace std;

class Uses {
public:
	// methods
	// Default constructor
	Uses();

	// API
	static void SetStmtUsesVar(int stmtUsing, int varUsed);
	static bool IsStmtUsingVar(int stmtUsing, int varUsed);
    static vector<int> GetStmtUsingVar(int varUsed);
    static vector<int> GetVarUsedByStmt(int stmtUsing);

	static bool HasAnyUses();
	static int SizeOfUses();

	static void ClearData();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

private:
	static map <int, vector<int> > stmtToVarTable;
    static map <int, vector<int> > varToStmtTable;
	static map <int, unsigned int> stmtToVarBitVector;
	// least significant bit will represent index 0

	static int sizeOfUses;

};
#endif
