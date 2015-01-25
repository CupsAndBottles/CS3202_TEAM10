#include <utility>
#include <map>
//#include <vector>
#include "Parent.h"
#include "Modifies.h"

using namespace std;

map <int, vector<int> > Modifies::StmtToVarTable;
map <int, vector<int> > Modifies::VarToStmtTable;

// empty constructor
Modifies::Modifies() {};

// API
void Modifies::SetStmtModifiesVar(int stmtModifying, int varModified) {
    if (!IsStmtModifyingVar(stmtModifying, varModified)) {
        StmtToVarTable[stmtModifying].push_back(varModified);
        VarToStmtTable[varModified].push_back(stmtModifying);
    }

    if (Parent::GetParentOf(stmtModifying) != -1) 
           SetStmtModifiesVar(Parent::GetParentOf(stmtModifying), varModified);
}

bool Modifies::IsStmtModifyingVar(int stmtModifying, int varModified) {
    if (StmtToVarTable.count(stmtModifying) != 0) {
		for (int i = 0; i < StmtToVarTable.at(stmtModifying).size(); i++) {
            if (StmtToVarTable.at(stmtModifying).at(i) == varModified) {
                return true;
			}
		}
	}
    
	return false;

	// try printing out # of variables that 'stmtModifying' has, 
	// it should be 1 all the time
}

vector<int> Modifies::GetStmtModifyingVar(int varModified) {
    
    if (VarToStmtTable.count(varModified) == 0) {
		vector<int> stmtsModifyingVarModified;
		return stmtsModifyingVarModified;

	}

    else { 
		return VarToStmtTable.at(varModified);

	}
}

vector<int> Modifies::GetVarModifiedByStmt(int stmtModifying) {
    
    if (StmtToVarTable.count(stmtModifying) == 0) {
		vector<int> varsModifyiedByStmtModifying;
		return varsModifyiedByStmtModifying;

	}
    
	else {
		return StmtToVarTable.at(stmtModifying);

	}

}


bool Modifies::HasAnyModifies() {
    return !StmtToVarTable.empty();

}

int Modifies::SizeOfModifies() {
    int sum = 0;
    
    for(map<int, vector<int> >::iterator it = StmtToVarTable.begin(); it!=StmtToVarTable.end(); it++) {
        sum += it->second.size();

	}
    
	return sum;
	// try Map::size() method
}

void Modifies::ClearData() {
	StmtToVarTable.clear();
	VarToStmtTable.clear();

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
