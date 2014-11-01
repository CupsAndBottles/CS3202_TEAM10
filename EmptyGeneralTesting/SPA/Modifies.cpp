#include <utility>
#include <map>
#include "Modifies.h"
#include <iostream>

using namespace std;

// empty constructor
Modifies::Modifies() {

};

// API
void Modifies::SetStmtModifiesVar(int stmtModifying, int varModified) {
    StmtToVarTable[stmtModifying].insert(varModified);
    VarToStmtTable[varModified].insert(stmtModifying);
}

bool Modifies::IsStmtModifiesVar(int stmtModifying, int varModified) {
    if (StmtToVarTable.count(stmtModifying)!=0)
        if (StmtToVarTable.at(stmtModifying).count(varModified)!=0)
            return true;
    return false;
}

set<int> Modifies::GetStmtModifyingVar(int varModified) {
    set<int> ret;
    if (VarToStmtTable.count(varModified)==0)
        return ret;
    else return VarToStmtTable.at(varModified);
}

set<int> Modifies::GetVarModifiedByStmt(int stmtModifying) {
    set<int> ret;
    if (StmtToVarTable.count(stmtModifying)==0)
        return ret;
    else return StmtToVarTable.at(stmtModifying);
}


bool Modifies::HasAnyModifies() {
    return !StmtToVarTable.empty();

}

int Modifies::SizeOfModifies() {
    return StmtToVarTable.size();
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
