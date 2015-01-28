#include <utility>
#include <map>
#include "Parent.h"
#include "Uses.h"

using namespace std;

map <unsigned int, vector<unsigned int> > Uses::stmtToVarTable;
map <unsigned int, vector<unsigned int> > Uses::varToStmtTable;
unsigned int Uses::sizeOfUses;

// empty constructor
Uses::Uses() {};

// API
void Uses::SetStmtUsesVar(unsigned int stmtUsing, unsigned int varUsed) {
    if (!IsStmtUsingVar(stmtUsing, varUsed)) {
        stmtToVarTable[stmtUsing].push_back(varUsed);
        varToStmtTable[varUsed].push_back(stmtUsing);

		sizeOfUses++;

    }

    if (Parent::GetParentOf(stmtUsing) != -1) {
        SetStmtUsesVar(Parent::GetParentOf(stmtUsing), varUsed);

	}

}

bool Uses::IsStmtUsingVar(unsigned int stmtUsing, unsigned int varUsed) {
    if (stmtToVarTable.count(stmtUsing) != 0) {
        for (unsigned int i = 0; i < stmtToVarTable.at(stmtUsing).size(); i++) {
            if (stmtToVarTable.at(stmtUsing).at(i) == varUsed) {
                return true;
			}
		}
	}

    return false;
}

vector<unsigned int> Uses::GetStmtUsingVar(unsigned int varUsed) {
  
    if (varToStmtTable.count(varUsed) == 0) {
		vector<unsigned int> stmtsUsingVarUsed;
		return stmtsUsingVarUsed;

	}

    else {
		return varToStmtTable.at(varUsed);

	}
}

vector<unsigned int> Uses::GetVarUsedByStmt(unsigned int stmtUsing) {
    
	if (stmtToVarTable.count(stmtUsing) == 0) {
		vector<unsigned int> varsUsedByStmtUsing;
		return varsUsedByStmtUsing;

	}
		
    else {
		return stmtToVarTable.at(stmtUsing);

	}

}


bool Uses::HasAnyUses() {
    return !stmtToVarTable.empty();

}

unsigned int Uses::SizeOfUses() {
     return sizeOfUses;

}

void Uses::ClearData() {
    stmtToVarTable.clear();
    varToStmtTable.clear();
	sizeOfUses = 0;

}


// driver code to test out Uses
/*
   unsigned int main() {
   cout << "testing driver program\n";
   cout << "0 to stop\n1 to setUses(stmt, var)\n2 to getUsesByStmt(stmt)\n3 to getUsesStmt(var)\n";
   unsigned int action;
   cin >> action;

   Uses obj = Uses();
   while (action!=0) {
   if (action==1) {
   unsigned int stmt, var;
   cin >> stmt >> var;
   obj.SetStmtUsesVar(stmt,var);
   }
   else if (action==2) {
   unsigned int stmt;
   cin >> stmt;
   set<unsigned int> foo = obj.GetVarUsedByStmt(stmt);

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
set<unsigned int> foo = obj.GetStmtUsingVar(var);

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
