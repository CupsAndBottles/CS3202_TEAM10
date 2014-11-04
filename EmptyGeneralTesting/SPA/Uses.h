#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Uses {
public:
	// methods
	// Default constructor
	Uses();

	// API
	void SetStmtUsesVar(int stmtUsing, int varUsed);
	bool IsStmtUsingVar(int stmtUsing, int varUsed);
    set<int> GetStmtUsingVar(int varUsed);
    set<int> GetVarUsedByStmt(int stmtUsing);

	bool HasAnyUses();
	int SizeOfUses();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

private:
	map <int, set<int> > StmtToVarTable;
    map <int, set<int> > VarToStmtTable;

};