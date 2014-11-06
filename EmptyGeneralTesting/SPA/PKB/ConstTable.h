#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ConstTable {
public:
	// methods\
	// Default constructor
	Uses();

	// API
	void SetStmtUsesConst(int stmtUsing, int varUsed);
	bool IsStmtUsingConst(int stmtUsing, int varUsed);
    set<int> GetStmtUsingConst(int varUsed);
    set<int> GetConstUsedByStmt(int stmtUsing);

	bool HasAnyUses();
	int SizeOfUses();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

private:
	map <int, set<int> > StmtToConstTable;
    map <int, set<int> > VarToConstTable;

};