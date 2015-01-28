#include <utility>
#include <map>
#include "Parent.h"
#include "Modifies.h"

using namespace std;

map <unsigned int, vector<unsigned int> > Modifies::stmtToVarTable;
map <unsigned int, vector<unsigned int> > Modifies::varToStmtTable;
unsigned int Modifies::sizeOfModifies;

// empty constructor
Modifies::Modifies() {};

// API
void Modifies::SetStmtModifiesVar(unsigned int stmtModifying, unsigned int varModified) {
    if (!IsStmtModifyingVar(stmtModifying, varModified)) {
        stmtToVarTable[stmtModifying].push_back(varModified);
        varToStmtTable[varModified].push_back(stmtModifying);

		sizeOfModifies++;

    }

    if (Parent::GetParentOf(stmtModifying) != -1) {
           SetStmtModifiesVar(Parent::GetParentOf(stmtModifying), varModified);

	}

}

bool Modifies::IsStmtModifyingVar(unsigned int stmtModifying, unsigned int varModified) {
    if (stmtToVarTable.count(stmtModifying) != 0) {
		for (unsigned int i = 0; i < stmtToVarTable.at(stmtModifying).size(); i++) {
            if (stmtToVarTable.at(stmtModifying).at(i) == varModified) {
                return true;
			}
		}
	}
    
	return false;

	// try printing out # of variables that 'stmtModifying' has, 
	// it should be 1 all the time
}

vector<unsigned int> Modifies::GetStmtModifyingVar(unsigned int varModified) {
    
    if (varToStmtTable.count(varModified) == 0) {
		vector<unsigned int> stmtsModifyingVarModified;
		return stmtsModifyingVarModified;

	}

    else { 
		return varToStmtTable.at(varModified);

	}
}

vector<unsigned int> Modifies::GetVarModifiedByStmt(unsigned int stmtModifying) {
    
    if (stmtToVarTable.count(stmtModifying) == 0) {
		vector<unsigned int> varsModifyiedByStmtModifying;
		return varsModifyiedByStmtModifying;

	}
    
	else {
		return stmtToVarTable.at(stmtModifying);

	}

}


bool Modifies::HasAnyModifies() {
    return !stmtToVarTable.empty();

}

unsigned int Modifies::SizeOfModifies() {
	return sizeOfModifies;

}

void Modifies::ClearData() {
	stmtToVarTable.clear();
	varToStmtTable.clear();
	sizeOfModifies = 0;

}

// driver code to test out Modifies
/*
unsigned int main() {
    cout << "testing driver program\n";
    cout << "0 to stop\n1 to setModifies(stmt, var)\n2 to getModifiesByStmt(stmt)\n3 to getModifiesStmt(var)\n";
    unsigned int action;
    cin >> action;

    Modifies obj = Modifies();
    while (action!=0) {
       if (action==1) {
           unsigned int stmt, var;
           cin >> stmt >> var;
           obj.SetStmtModifiesVar(stmt,var);
       }
       else if (action==2) {
           unsigned int stmt;
           cin >> stmt;
           set<unsigned int> foo = obj.GetVarModifiedByStmt(stmt);

           //print out all elems in set
           set<unsigned int>::iterator it;
           for (it=foo.begin(); it!=foo.end(); it++) {
               cout << *it << " ";
           }
           cout << endl;
       }
       else if (action==3) {
           unsigned int var;
           cin >> var;
           set<unsigned int> foo = obj.GetStmtModifyingVar(var);

           //print out all elems in set
           set<unsigned int>::iterator it;
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
