#ifndef MODIFIES_H
#define MODIFIES_H

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
        static void SetStmtModifiesVar(int stmtModifying, int varModified); 
        static bool IsStmtModifiesVar(int stmtModifying, int varModified);
        static set<int> GetStmtModifyingVar(int varModified);		// Modifies (_, "x")
        static set<int> GetVarModifiedByStmt(int stmtModifying);	// Modifies (2, _)
		// Select s such that Modifies(w, "x")
		// 1. go VarTable, GetIndexOf("x")
		// 2. GetStmtModifyingVar(index of x)
		// 3. StmtTypeTable, filter w

        static bool HasAnyModifies();
        static int SizeOfModifies();
		static void ClearData();

        // APIs out of scope of assigment 4
        /*void SetModifiesProc(int procModifying, int varModified);
          bool IsModifiesProc(int procModifying, int varModified);
          vector<int> GetModifiesProc(int varModified);
          vector<int> GetModifiedByProc(int procModifying);*/

    private:
        static map <int, set<int> > StmtToVarTable;
        static map <int, set<int> > VarToStmtTable;
        // insert other private methods here

};
#endif