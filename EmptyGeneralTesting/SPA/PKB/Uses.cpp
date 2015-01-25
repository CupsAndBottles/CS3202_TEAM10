#include <utility>
#include <map>
#include "Parent.h"
#include "Uses.h"

using namespace std;

map <int, vector<int> > Uses::stmtToVarTable;
map <int, vector<int> > Uses::varToStmtTable;
int Uses::sizeOfUses;

// empty constructor
Uses::Uses() {};

// API
void Uses::SetStmtUsesVar(int stmtUsing, int varUsed) {
    if (!IsStmtUsingVar(stmtUsing, varUsed)) {
        stmtToVarTable[stmtUsing].push_back(varUsed);
        varToStmtTable[varUsed].push_back(stmtUsing);

		sizeOfUses++;

    }

    if (Parent::GetParentOf(stmtUsing) != -1) {
        SetStmtUsesVar(Parent::GetParentOf(stmtUsing), varUsed);

	}

}

bool Uses::IsStmtUsingVar(int stmtUsing, int varUsed) {
    if (stmtToVarTable.count(stmtUsing) != 0) {
        for (int i = 0; i < stmtToVarTable.at(stmtUsing).size(); i++) {
            if (stmtToVarTable.at(stmtUsing).at(i) == varUsed) {
                return true;
			}
		}
	}

    return false;
}

vector<int> Uses::GetStmtUsingVar(int varUsed) {
  
    if (varToStmtTable.count(varUsed) == 0) {
		vector<int> stmtsUsingVarUsed;
		return stmtsUsingVarUsed;

	}

    else {
		return varToStmtTable.at(varUsed);

	}
}

vector<int> Uses::GetVarUsedByStmt(int stmtUsing) {
    
	if (stmtToVarTable.count(stmtUsing) == 0) {
		vector<int> varsUsedByStmtUsing;
		return varsUsedByStmtUsing;

	}
		
    else {
		return stmtToVarTable.at(stmtUsing);

	}

}


bool Uses::HasAnyUses() {
    return !stmtToVarTable.empty();

}

int Uses::SizeOfUses() {
     return sizeOfUses;

}

void Uses::ClearData() {
    stmtToVarTable.clear();
    varToStmtTable.clear();
	sizeOfUses = 0;

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
