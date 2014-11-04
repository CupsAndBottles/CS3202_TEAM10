#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Modifies {
    public:
        // methods
       // Default constructor
        Modifies();

        // API
        void SetStmtModifiesVar(int stmtModifying, int varModified); 
        bool IsStmtModifiesVar(int stmtModifying, int varModified);
        set<int> GetStmtModifyingVar(int varModified);
        set<int> GetVarModifiedByStmt(int stmtModifying);

        bool HasAnyModifies();
        int SizeOfModifies();

        // APIs out of scope of assigment 4
        /*void SetModifiesProc(int procModifying, int varModified);
          bool IsModifiesProc(int procModifying, int varModified);
          vector<int> GetModifiesProc(int varModified);
          vector<int> GetModifiedByProc(int procModifying);*/

    private:
        map <int, set<int> > StmtToVarTable;
        map <int, set<int> > VarToStmtTable;
        // insert other private methods here

};