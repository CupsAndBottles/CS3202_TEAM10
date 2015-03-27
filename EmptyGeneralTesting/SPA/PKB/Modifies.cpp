#include <vector>
#include <map>

#include "Parent.h"
#include "Calls.h"
#include "Modifies.h"

using namespace std;

map <int, vector<int>> Modifies::stmtToVarTable;
map <int, vector<int>> Modifies::varToStmtTable;
map <int, vector<int>> Modifies::procToVarTable;
map <int, vector<int>> Modifies::varToProcTable;
bool Modifies::bitVectorIsBuilt;
int Modifies::sizeOfModifies;
int Modifies::maxStmtOrVar;
int Modifies::maxProcOrVar;
vector<vector<bool>> Modifies::stmtToVarBitVector;
vector<vector<bool>> Modifies::procToVarBitVector;
		
Modifies::Modifies() {
	bitVectorIsBuilt = false;
	sizeOfModifies = 0;
};

// API
void Modifies::SetStmtModifiesVar(int stmtModifying, int varModified) {
	if (!IsStmtModifyingVar(stmtModifying, varModified)) {
        stmtToVarTable[stmtModifying].push_back(varModified);
        varToStmtTable[varModified].push_back(stmtModifying);

		sizeOfModifies++;

    }
}

bool Modifies::IsStmtModifyingVar(int stmtModifying, int varModified) {

		if (stmtToVarTable.count(stmtModifying) != 0) {
			for (vector<int>::iterator it = stmtToVarTable[stmtModifying].begin(); it != stmtToVarTable[stmtModifying].end(); it++) {
				if (*it == varModified)
					return true;
			}
		
		}
		return false;
	}



vector<int> Modifies::GetStmtModifyingVar(int varModified) {    
    if (varToStmtTable.count(varModified) == 0) {
		vector<int> stmtsModifyingVarModified;
		return stmtsModifyingVarModified;

	} else { 
		return varToStmtTable.at(varModified);

	}
}

vector<int> Modifies::GetVarModifiedByStmt(int stmtModifying) {
    if (stmtToVarTable.count(stmtModifying) == 0) {
		vector<int> varsModifyiedByStmtModifying;
		return varsModifyiedByStmtModifying;

	} else {
		return stmtToVarTable.at(stmtModifying);

	}

}

void Modifies::SetProcModifiesVar(int procModifying, int varModified) {
	if (!IsProcModifyingVar(procModifying, varModified)) {
        procToVarTable[procModifying].push_back(varModified);
        varToProcTable[varModified].push_back(procModifying);

		sizeOfModifies++;

    }
}

bool Modifies::IsProcModifyingVar(int procModifying, int varModified) {
	if (bitVectorIsBuilt) {
		// not implemented yet
		return false; // dummy value
	} else {
		if (procToVarTable.count(procModifying) != 0) {
			for (vector<int>::iterator it = procToVarTable[procModifying].begin(); it != procToVarTable[procModifying].end(); it++) {
				if (*it == varModified)
					return true;
			}
		
		}
		return false;
	}

}

vector<int> Modifies::GetProcModifyingVar(int varModified) {
	if (varToProcTable.count(varModified) == 0) {
		vector<int> procsModifyingVarModified;
		return procsModifyingVarModified;

	} else { 
		return varToProcTable.at(varModified);

	}

}

vector<int> Modifies::GetVarModifiedByProc(int procModifying) {
	if (procToVarTable.count(procModifying) == 0) {
		vector<int> varsModifyiedByProcModifying;
		return varsModifyiedByProcModifying;

	} else {
		return procToVarTable.at(procModifying);

	}

}

bool Modifies::HasAnyModifies() {
    return !stmtToVarTable.empty();

}

int Modifies::SizeOfModifies() {
	return sizeOfModifies;

}

void Modifies::ClearData() {
	stmtToVarTable.clear();
	varToStmtTable.clear();
	procToVarTable.clear();
	varToProcTable.clear();
	sizeOfModifies = 0;

}

// driver code to test out Modifies
/*
int main() {
    cout << "testing driver program\n";
    cout << "0 to stop\n1 to setModifies(stmt, var)\n2 to getModifiesByStmt(stmt)\n3 to getModifiesStmt(var)\n";
    int action;
    cin >> action;

    Modifies obj = Modifies();
    while (action!=0) {
       if (action==1) {
           int stmt, var;
           cin >> stmt >> var;
           obj.SetStmtModifiesVar(stmt,var);
       }
       else if (action==2) {
           int stmt;
           cin >> stmt;
           set<int> foo = obj.GetVarModifiedByStmt(stmt);

           //print out all elems in set
           set<int>::iterator it;
           for (it=foo.begin(); it!=foo.end(); it++) {
               cout << *it << " ";
           }
           cout << endl;
       }
       else if (action==3) {
           int var;
           cin >> var;
           set<int> foo = obj.GetStmtModifyingVar(var);

           //print out all elems in set
           set<int>::iterator it;
           for (it=foo.begin(); it!=foo.end(); it++) {
               cout << *it << " ";
           }
           cout << endl;
       }
       else cout << "action not recognized\n";
       cin >> action;
    }

    return 0;
}
*/
