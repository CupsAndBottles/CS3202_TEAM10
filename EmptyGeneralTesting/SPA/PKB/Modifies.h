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
        static void SetStmtModifiesVar(unsigned int stmtModifying, unsigned int varModified); 
        static bool IsStmtModifyingVar(unsigned int stmtModifying, unsigned int varModified);
        static vector<unsigned int> GetStmtModifyingVar(unsigned int varModified);		// Modifies (_, "x")
        static vector<unsigned int> GetVarModifiedByStmt(unsigned int stmtModifying);		// Modifies (2, _)
		
        static bool HasAnyModifies();
<<<<<<< HEAD
		
		// helper methods for testing
		static int SizeOfModifies();
=======
        static unsigned int SizeOfModifies();

>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
		static void ClearData();

        // APIs out of scope of assigment 4
        /*void SetModifiesProc(unsigned int procModifying, unsigned int varModified);
          bool IsModifiesProc(unsigned int procModifying, unsigned int varModified);
          vector<unsigned int> GetModifiesProc(unsigned int varModified);
          vector<unsigned int> GetModifiedByProc(unsigned int procModifying);*/

    private:
        static map <unsigned int, vector<unsigned int> > stmtToVarTable;
        static map <unsigned int, vector<unsigned int> > varToStmtTable;
		static unsigned int sizeOfModifies;

};
#endif
