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
	static void SetStmtUsesConst(unsigned int stmtUsing, unsigned int constUsed);
	static bool IsStmtUsingConst(unsigned int stmtUsing, unsigned int constUsed);
    static vector<unsigned int> GetStmtUsingConst(unsigned int constUsed);
    static vector<unsigned int> GetConstUsedByStmt(unsigned int stmtUsing);

	static bool HasAnyConst();
    static vector<unsigned int> GetAllConst();
	static unsigned int SizeOfConstTable();
    static void ClearData();

	// APIs out of scope of assigment 4
	/*void SetUsesProc(unsigned int procUsing, unsigned int varUsed);
	bool IsUsesProc(unsigned int procUsing, unsigned int varUsed);
	vector<unsigned int> GetUsesProc(unsigned int varUsed);
	vector<unsigned int> GetUsedByProc(unsigned int procUsing);*/

private:
	static map <unsigned int, vector<unsigned int> > StmtToConstTable;
    static map <unsigned int, vector<unsigned int> > ConstToStmtTable;

};
