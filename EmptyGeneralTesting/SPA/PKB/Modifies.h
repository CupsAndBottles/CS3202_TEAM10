#ifndef MODIFIES_H
#define MODIFIES_H

#include <utility>
#include <vector>
#include <map>

using namespace std;

class Modifies {
    public:
		// methods
		// Default constructor
        Modifies();

        // API
        static void SetStmtModifiesVar(int stmtModifying, int varModified); 
        static bool IsStmtModifyingVar(int stmtModifying, int varModified);
        static vector<int> GetStmtModifyingVar(int varModified);
		static vector<int> GetVarModifiedByStmt(int stmtModifying);

		static void SetProcModifiesVar(int procModifying, int varModified);
		static bool IsProcModifyingVar(int procModifying, int varModified);
		static vector<int> GetProcModifyingVar(int varModified);
		static vector<int> GetVarModifiedByProc(int procModifying);

        static bool HasAnyModifies();
		
		// helper methods for testing
        static int SizeOfModifies();
		static void ClearData();

    private:
        static map <int, vector<int>> stmtToVarTable;
        static map <int, vector<int>> varToStmtTable;
		static map <int, vector<bool>> stmtToVarBitVector;
		// least significant bit will represent index 0

		static map <int, vector<int>> procToVarTable;
		static map <int, vector<int>> varToProcTable;
		static map <int, vector<bool>> procToVarBitVector;
		// initailise to size 32

		static int sizeOfModifies;

		static void SetStmtToVarBitVector(int stmtModifying, int varModified);
		static void SetProcToVarBitVector(int procModifying, int varModified);

};
#endif
