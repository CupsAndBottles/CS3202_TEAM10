#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include "ProcTable.h"
#include "Parent.h"

using namespace std;

map <int, vector<int> > ProcTable::StmtToProcTable;
map <int, vector<int> > ProcTable::ProcToStmtTable;

// empty constructor
ProcTable::ProcTable() {}

// API
void ProcTable::SetStmtUsesProc(int stmtUsing, int procUsed) {
    if (!IsStmtUsingConst(stmtUsing, procUsed)) {
        StmtToProcTable[stmtUsing].push_back(procUsed);
        ProcToStmtTable[procUsed].push_back(stmtUsing);
    }

    if (Parent::GetParentOf(stmtUsing) != -1)
        SetStmtUsesProc(Parent::GetParentOf(stmtUsing), procUsed);
}

bool ProcTable::IsStmtUsingProc(int stmtUsing, int procUsed) {
    if (StmtToProcTable.count(stmtUsing)!=0)
        for (unsigned int i=0; i<StmtToProcTable.at(stmtUsing).size(); i++)
            if (StmtToProcTable.at(stmtUsing).at(i) == procUsed)
                return true;
    return false;
}

vector<int> ProcTable::GetStmtUsingProc(int procUsed) {
    vector<int> ret;
    if (ProcToStmtTable.count(procUsed)==0)
        return ret;
    else return ProcToStmtTable.at(procUsed);
}

vector<int> ProcTable::GetProcUsedByStmt(int stmtUsing) {
    vector<int> ret;
    if (StmtToProcTable.count(stmtUsing)==0)
        return ret;
    else return StmtToProcTable.at(stmtUsing);
}


bool ProcTable::HasAnyProc() {
    return !StmtToProcTable.empty();

}

vector<int> ProcTable::GetAllProc() {
    vector<int> listOfProcedures;

    for(map<int, vector<int> >::iterator it = StmtToProcTable.begin(); it != StmtToProcTable.end(); it++) {
        for(unsigned int i = 0; i < it->second.size(); i++) {
            listOfProcedures.push_back(it->second.at(i));
		}
	}

	sort(listOfProcedures.begin(), listOfProcedures.end());
	
	vector<int>::iterator it;
	it = unique (listOfProcedures.begin(), listOfProcedures.end()); 
	listOfProcedures.resize(distance(listOfProcedures.begin(),it) ); // trims excess spaces in vector

    return listOfProcedures;
}

int ProcTable::SizeOfProcTable() {
    int sum = 0;

    for(map<int, vector<int> >::iterator it=StmtToProcTable.begin(); it!=StmtToProcTable.end();        it++)
    sum += it->second.size();
    
	return sum;
}

void ProcTable::ClearData() {
    StmtToProcTable.clear();
    ProcToStmtTable.clear();
}
