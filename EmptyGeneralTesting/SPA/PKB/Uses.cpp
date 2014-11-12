#include <utility>
#include <map>
#include <vector>
#include "Uses.h"
#include "Parent.h"

using namespace std;

map <int, vector<int> > Uses::StmtToVarTable;
map <int, vector<int> > Uses::VarToStmtTable;

// empty constructor
Uses::Uses() {}

// API
void Uses::SetStmtUsesVar(int stmtUsing, int varUsed) {
    if (!IsStmtUsingVar(stmtUsing, varUsed)) {
        StmtToVarTable[stmtUsing].push_back(varUsed);
        VarToStmtTable[varUsed].push_back(stmtUsing);
    }

    if (Parent::GetParentOf(stmtUsing) != -1)
        SetStmtUsesVar(Parent::GetParentOf(stmtUsing), varUsed);
}

bool Uses::IsStmtUsingVar(int stmtUsing, int varUsed) {
    if (StmtToVarTable.count(stmtUsing)!=0)
        for (int i=0; i<StmtToVarTable.at(stmtUsing).size(); i++)
            if (StmtToVarTable.at(stmtUsing).at(i) == varUsed)
                return true;
    return false;
}

vector<int> Uses::GetStmtUsingVar(int varUsed) {
    vector<int> ret;
    if (VarToStmtTable.count(varUsed)==0)
        return ret;
    else return VarToStmtTable.at(varUsed);
}

vector<int> Uses::GetVarUsedByStmt(int stmtUsing) {
    vector<int> ret;
    if (StmtToVarTable.count(stmtUsing)==0)
        return ret;
    else return StmtToVarTable.at(stmtUsing);
}


bool Uses::HasAnyUses() {
    return !StmtToVarTable.empty();

}

int Uses::SizeOfUses() {
    return StmtToVarTable.size();
}

void Uses::ClearData() 
{
    StmtToVarTable.clear();
    VarToStmtTable.clear();
}


// driver code to test out Uses
/*
   int main() {
   cout << "testing driver program\n";
   cout << "0 to stop\n1 to setUses(stmt, var)\n2 to getUsesByStmt(stmt)\n3 to getUsesStmt(var)\n";
   int action;
   cin >> action;

   Uses obj = Uses();
   while (action!=0) {
   if (action==1) {
   int stmt, var;
   cin >> stmt >> var;
   obj.SetStmtUsesVar(stmt,var);
   }
   else if (action==2) {
   int stmt;
   cin >> stmt;
   set<int> foo = obj.GetVarUsedByStmt(stmt);

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
set<int> foo = obj.GetStmtUsingVar(var);

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
