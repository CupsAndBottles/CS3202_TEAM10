#include <utility>
#include <vector>

using namespace std;

class Modifies {
public:
	// methods
	// Default constructor
	Modifies();

	// API
	void SetModifiesStmt(int stmtModifying, int varModified); // additional args: stmt type?
	bool IsModifiesStmt(int stmtModifying, int varModified);
	vector<int> GetModifiesStmt(int varModified);
	vector<int> GetModifiedByStmt(int stmtModifying);

	bool HasAnyModifies();

	// APIs out of scope of assigment 4
	/*void SetModifiesProc(int procModifying, int varModified);
	bool IsModifiesProc(int procModifying, int varModified);
	vector<int> GetModifiesProc(int varModified);
	vector<int> GetModifiedByProc(int procModifying);*/

private:
	// variables
	vector<pair<int, int>> modifiesStmtTable;	// List of Modifies(s, v) relationships
	/*vector<pair<int, int>> modifiesProcTable;	// List of Modifies(p, v) relationships*/

	// insert other private methods here

};