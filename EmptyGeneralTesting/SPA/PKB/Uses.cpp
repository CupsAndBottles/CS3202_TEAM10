#include <utility>
#include <map>

#include "Parent.h"
#include "Calls.h"
#include "Uses.h"

using namespace std;

map <int, vector<int>> Uses::stmtToVarTable;
map <int, vector<int>> Uses::varToStmtTable;
map <int, vector<int>> Uses::procToVarTable;
map <int, vector<int>> Uses::varToProcTable;
vector<vector<bool>> Uses::stmtToVarBitVector;
vector<vector<bool>> Uses::procToVarBitVector;
bool Uses::bitVectorIsBuilt;
int Uses::sizeOfUses;
int maxNoOfVar;
int maxNoOfLines;
int maxNoOfProc;

Uses::Uses() {
	bitVectorIsBuilt = false;
	sizeOfUses = 0;
	maxNoOfVar=0;
	maxNoOfLines=0;
	maxNoOfProc=0;
};

// API
void Uses::SetStmtUsesVar(int stmtUsing, int varUsed) {
    if (!IsStmtUsingVar(stmtUsing, varUsed)) {
        stmtToVarTable[stmtUsing].push_back(varUsed);
        varToStmtTable[varUsed].push_back(stmtUsing);
	
		sizeOfUses++;
		maxNoOfLines = maxNoOfLines > stmtUsing ? maxNoOfLines : stmtUsing;
		maxNoOfVar = maxNoOfVar > varUsed ? maxNoOfVar : varUsed;
		// initialize if not yet done
		if (!bitVectorIsBuilt) {
			std::vector<vector<bool>> stmtToVarBitVector (maxNoOfLines, 0);
			bitVectorIsBuilt = true;
		}
		// if the current number of lines is bigger than size of bitVector, expand
		std::vector <bool> a;
		while (stmtToVarBitVector.size()!=maxNoOfLines) {
			stmtToVarBitVector.push_back(a);
		}
		for (int i=0;i<maxNoOfVar;i++) {
			while (stmtToVarBitVector[i].size()!=maxNoOfVar)
				stmtToVarBitVector[i].push_back(0);
		}
		// after expanding, insert the new Next r'ship
		stmtToVarBitVector[stmtUsing][varUsed]=1;
    }

    if (Parent::GetParentOf(stmtUsing) != -1) {
        SetStmtUsesVar(Parent::GetParentOf(stmtUsing), varUsed);

	}

}


bool Uses::IsStmtUsingVar(int stmtUsing, int varUsed) {
   if (!bitVectorIsBuilt) {
		return false; 
	} else {
		if (stmtToVarTable.count(stmtUsing) != 0) {
			for (vector<int>::iterator it = stmtToVarTable[stmtUsing].begin(); it != stmtToVarTable[stmtUsing].end(); it++) {
				if (*it == varUsed)
					return true;
			}
		
		}
		return false;
	}

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

		sizeOfUses++;

    }
		maxNoOfProc = maxNoOfProc > procUsing ? maxNoOfProc : procUsing;
		maxNoOfVar = maxNoOfVar > varUsed ? maxNoOfVar : varUsed;
		// initialize if not yet done
		if (!bitVectorIsBuilt) {
			std::vector<vector<bool>> procToVarBitVector (maxNoOfProc, 0);
			bitVectorIsBuilt = true;
		}
		// if the current number of lines is bigger than size of bitVector, expand
		std::vector <bool> a;
		while (procToVarBitVector.size()!=maxNoOfProc) {
			procToVarBitVector.push_back(a);
		}
		for (int i=0;i<maxNoOfVar;i++) {
			while (procToVarBitVector[i].size()!=maxNoOfVar)
				procToVarBitVector[i].push_back(0);
		}
		// after expanding, insert the new Next r'ship
		procToVarBitVector[procUsing][varUsed]=1;

	vector<int> procsCalling = Calls::GetProcsCalling(procUsing);
	if (procsCalling.size() > 0) {
		for (unsigned int i = 0; i < procsCalling.size(); i++)
			SetProcUsesVar(procsCalling.at(i), varUsed);

	}

}

bool Uses::IsProcUsingVar(int procUsing, int varUsed) {
	if (bitVectorIsBuilt) {
		/*if (procToVarBitVector.count(procUsing) != 0)
		if (varUsed < (int) procToVarBitVector[procUsing].size())
			return procToVarBitVector[procUsing].at(varUsed);
	
		return false;*/ // old reusable code
		return false; // dummy value
	} else {
		if (procToVarTable.count(procUsing) != 0) {
			for (vector<int>::iterator it = procToVarTable[procUsing].begin(); it != procToVarTable[procUsing].end(); it++) {
				if (*it == varUsed)
					return true;
			}
		
		}
		return false;
	}

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
	procToVarTable.clear();
	varToProcTable.clear();
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
