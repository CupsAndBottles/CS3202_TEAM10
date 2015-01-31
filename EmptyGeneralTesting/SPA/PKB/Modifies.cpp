#include <utility>
#include <map>
#include "Parent.h"
#include "Modifies.h"

using namespace std;

map <int, vector<int> > Modifies::stmtToVarTable;
map <int, vector<int> > Modifies::varToStmtTable;
map <int, unsigned int> Modifies::stmtToVarBitVector;
int Modifies::sizeOfModifies;

// empty constructor
Modifies::Modifies() {};

// API
void Modifies::SetStmtModifiesVar(int stmtModifying, int varModified) {
    if (!IsStmtModifyingVar(stmtModifying, varModified)) {
        stmtToVarTable[stmtModifying].push_back(varModified);
        varToStmtTable[varModified].push_back(stmtModifying);

		unsigned int newVar = 1 << varModified;
		stmtToVarBitVector[stmtModifying] = newVar | stmtToVarBitVector[stmtModifying];

		sizeOfModifies++;

    }

    if (Parent::GetParentOf(stmtModifying) != -1) {
           SetStmtModifiesVar(Parent::GetParentOf(stmtModifying), varModified);

	}

}

bool Modifies::IsStmtModifyingVar(int stmtModifying, int varModified) {
    if (stmtToVarBitVector.count(stmtModifying) != 0) {
		unsigned int check = (1 << varModified) & stmtToVarBitVector[stmtModifying];
		return check != 0;
	}
	
	return false;

}

vector<int> Modifies::GetStmtModifyingVar(int varModified) {
    
    if (varToStmtTable.count(varModified) == 0) {
		vector<int> stmtsModifyingVarModified;
		return stmtsModifyingVarModified;

	}

    else { 
		return varToStmtTable.at(varModified);

	}
}

vector<int> Modifies::GetVarModifiedByStmt(int stmtModifying) {
    
    if (stmtToVarTable.count(stmtModifying) == 0) {
		vector<int> varsModifyiedByStmtModifying;
		return varsModifyiedByStmtModifying;

	}
    
	else {
		return stmtToVarTable.at(stmtModifying);

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
	stmtToVarBitVector.clear();
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
