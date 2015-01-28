#ifndef MODIFIES_H
#define MODIFIES_H

#include <utility>
#include <vector>
#include <map>
//#include <set>

using namespace std;

class Modifies {
    public:
		// methods
		// Default constructor
        Modifies();

        // API
        static void SetStmtModifiesVar(int stmtModifying, int varModified); 
        static bool IsStmtModifyingVar(int stmtModifying, int varModified);
        static vector<int> GetStmtModifyingVar(int varModified);		// Modifies (_, "x")
        static vector<int> GetVarModifiedByStmt(int stmtModifying);		// Modifies (2, _)
		
        static bool HasAnyModifies();
		
		// helper methods for testing
		static int SizeOfModifies();
		static void ClearData();

        // APIs out of scope of assigment 4
        /*void SetModifiesProc(int procModifying, int varModified);
          bool IsModifiesProc(int procModifying, int varModified);
          vector<int> GetModifiesProc(int varModified);
          vector<int> GetModifiedByProc(int procModifying);*/

    private:
        static map <int, vector<int> > stmtToVarTable;
        static map <int, vector<int> > varToStmtTable;
		static int sizeOfModifies;

};
#endif
