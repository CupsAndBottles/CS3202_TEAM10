#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ConstTable {
public:
	// methods\
	// Default constructor
	ConstTable();

	// API
	static void SetStmtUsesConst(int stmtUsing, int constUsed);
	static bool IsStmtUsingConst(int stmtUsing, int constUsed);
    static vector<int> GetStmtUsingConst(int constUsed);
    static vector<int> GetConstUsedByStmt(int stmtUsing);

	static bool HasAnyConst();
    static vector<int> GetAllConst();
	static int SizeOfConstTable();
    static void ClearData();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(int procUsing, int varUsed);
	bool IsUsesProc(int procUsing, int varUsed);
	vector<int> GetUsesProc(int varUsed);
	vector<int> GetUsedByProc(int procUsing);*/

	// insert subsequent columns of the ConstTable here
	// static map<int, vector<int>> stmtToConstTable
	// static map<int, vector<int>> procToConstTable

private:
	static map <int, vector<int> > stmtToConstTable;
    static map <int, vector<int> > constToStmtTable;

};
