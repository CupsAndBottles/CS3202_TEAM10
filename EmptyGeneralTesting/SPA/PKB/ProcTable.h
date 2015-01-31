#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ProcTable {
public:
	// methods\
	// Default constructor
	ProcTable();

	// API
	static void SetStmtUsesProc(int stmtUsing, int procUsed);
	static bool IsStmtUsingProc(int stmtUsing, int procUsed);
    static vector<int> GetStmtUsingProc(int procUsed);
    static vector<int> GetProcUsedByStmt(int stmtUsing);

	static bool HasAnyProc();
    static vector<int> GetAllProc();
	static int SizeOfProcTable();
    static void ClearData();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

private:
	static map <int, vector<int> > StmtToProcTable;
    static map <int, vector<int> > ProcToStmtTable;

};
