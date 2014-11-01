#include <utility>
#include <vector>

using namespace std;

class Uses {
public:
	// methods
	// Default constructor
	Uses();

	// API
	void SetUsesStmt(int stmtUsing, int varUsed); // additional args: stmt type?
	bool IsUsesStmt(int stmtUsing, int varUsed);
	vector<int> GetUsesStmt(int varUsed);
	vector<int> GetUsedByStmt(int stmtUsing);

	bool HasAnyUses();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

private:
	// variables
	vector<pair<int, int>> usesStmtTable;	// List of Modifies(s, v) relationships
	/*vector<pair<int, int>> usesProcTable;	// List of Modifies(p, v) relationships*/

	// insert other private methods here

};