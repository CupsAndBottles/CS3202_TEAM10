#include <utility>
#include <map>
#include "Parent.h"
#include "Calls.h"
#include "Uses.h"

using namespace std;

map <int, vector<int>> Uses::stmtToVarTable;
map <int, vector<int>> Uses::varToStmtTable;
map <int, vector<bool>> Uses::stmtToVarBitVector;
map <int, vector<int>> Uses::procToVarTable;
map <int, vector<int>> Uses::varToProcTable;
map <int, vector<bool>> Uses::procToVarBitVector;
int Uses::sizeOfUses;

// empty constructor
Uses::Uses() {};

// API
void Uses::SetStmtUsesVar(int stmtUsing, int varUsed) {
    if (!IsStmtUsingVar(stmtUsing, varUsed)) {
        stmtToVarTable[stmtUsing].push_back(varUsed);
        varToStmtTable[varUsed].push_back(stmtUsing);

		SetStmtToVarBitVector(stmtUsing, varUsed);
		
		sizeOfUses++;

    }

    if (Parent::GetParentOf(stmtUsing) != -1) {
        SetStmtUsesVar(Parent::GetParentOf(stmtUsing), varUsed);

	}

}

void Uses::SetStmtToVarBitVector(int stmtUsing, int varUsed) {
	if ((varUsed + 1) > (int) stmtToVarBitVector[stmtUsing].size()) {
		for (int i = 0; i < ((varUsed + 1) * 2); i++) {
			stmtToVarBitVector[stmtUsing].push_back(false);
		}
	} 
	
	stmtToVarBitVector[stmtUsing].at(varUsed) = true;

}

bool Uses::IsStmtUsingVar(int stmtUsing, int varUsed) {
   if (stmtToVarBitVector.count(stmtUsing) != 0)
		if (varUsed < (int) stmtToVarBitVector[stmtUsing].size())
		return stmtToVarBitVector[stmtUsing].at(varUsed);
	
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

	} else {
		return stmtToVarTable.at(stmtUsing);

	}

}

void Uses::SetProcUsesVar(int procUsing, int varUsed) {
	if (!IsProcUsingVar(procUsing, varUsed)) {
        procToVarTable[procUsing].push_back(varUsed);
        varToProcTable[varUsed].push_back(procUsing);
		
		SetProcToVarBitVector(procUsing, varUsed);

		sizeOfUses++;

    }

	vector<int> procsCalling = Calls::GetProcsCalling(procUsing);
	if (procsCalling.size() > 0) {
		for (unsigned int i = 0; i < procsCalling.size(); i++)
			SetProcUsesVar(procsCalling.at(i), varUsed);

	}

}

void Uses::SetProcToVarBitVector(int procUsing, int varused) {
	if ((varused + 1) > (int) procToVarBitVector[procUsing].size()) {
		for (int i = 0; i < ((varused + 1) * 2); i++) {
			procToVarBitVector[procUsing].push_back(false);
		}
		
	} 
	
	procToVarBitVector[procUsing].at(varused) = true;

}

bool Uses::IsProcUsingVar(int procUsing, int varUsed) {
	if (procToVarBitVector.count(procUsing) != 0)
		if (varUsed < (int) procToVarBitVector[procUsing].size())
			return procToVarBitVector[procUsing].at(varUsed);
	
	return false;

}

vector<int> Uses::GetProcUsingVar(int varUsed) {
	if (varToProcTable.count(varUsed) == 0) {
		vector<int> procsUsingVarUsed;
		return procsUsingVarUsed;

	} else { 
		return varToProcTable.at(varUsed);

	}

}

vector<int> Uses::GetVarUsedByProc(int procUsing) {
	if (procToVarTable.count(procUsing) == 0) {
		vector<int> varsUsedByProcUsing;
		return varsUsedByProcUsing;

	} else {
		return procToVarTable.at(procUsing);

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
	stmtToVarBitVector.clear();
	procToVarTable.clear();
	varToProcTable.clear();
	procToVarBitVector.clear();
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
