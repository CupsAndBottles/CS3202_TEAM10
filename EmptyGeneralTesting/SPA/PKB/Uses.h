#ifndef USES_H
#define USES_H

#include <utility>
//#include <vector>
#include <map>
#include <set>

using namespace std;

class Uses {
public:
	// methods
	// Default constructor
	Uses();

	// API
	static void SetStmtUsesVar(unsigned int stmtUsing, unsigned int varUsed);
	static bool IsStmtUsingVar(unsigned int stmtUsing, unsigned int varUsed);
    static vector<unsigned int> GetStmtUsingVar(unsigned int varUsed);
    static vector<unsigned int> GetVarUsedByStmt(unsigned int stmtUsing);

	static bool HasAnyUses();
	static unsigned int SizeOfUses();

	static void ClearData();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(unsigned int procUsing, unsigned int varUsed);
	bool IsUsesProc(unsigned int procUsing, unsigned int varUsed);
	vector<unsigned int> GetUsesProc(unsigned int varUsed);
	vector<unsigned int> GetUsedByProc(unsigned int procUsing);*/

private:
	static map <unsigned int, vector<unsigned int> > stmtToVarTable;
    static map <unsigned int, vector<unsigned int> > varToStmtTable;
	static unsigned int sizeOfUses;

};
#endif
