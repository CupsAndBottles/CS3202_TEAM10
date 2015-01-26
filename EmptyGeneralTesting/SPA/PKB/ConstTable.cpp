#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#include "ConstTable.h"
#include "Parent.h"

using namespace std;

map <int, vector<int> > ConstTable::StmtToConstTable;
map <int, vector<int> > ConstTable::ConstToStmtTable;

// empty constructor
ConstTable::ConstTable() {}

// API
void ConstTable::SetStmtUsesConst(int stmtUsing, int constUsed) {
    if (!IsStmtUsingConst(stmtUsing, constUsed)) {
        StmtToConstTable[stmtUsing].push_back(constUsed);
        ConstToStmtTable[constUsed].push_back(stmtUsing);
    }

    if (Parent::GetParentOf(stmtUsing) != -1)
        SetStmtUsesConst(Parent::GetParentOf(stmtUsing), constUsed);
}

bool ConstTable::IsStmtUsingConst(int stmtUsing, int constUsed) {
    if (StmtToConstTable.count(stmtUsing)!=0)
        for (int i=0; i<StmtToConstTable.at(stmtUsing).size(); i++)
            if (StmtToConstTable.at(stmtUsing).at(i) == constUsed)
                return true;
    return false;
}

vector<int> ConstTable::GetStmtUsingConst(int constUsed) {
    vector<int> ret;
    if (ConstToStmtTable.count(constUsed)==0)
        return ret;
    else return ConstToStmtTable.at(constUsed);
}

vector<int> ConstTable::GetConstUsedByStmt(int stmtUsing) {
    vector<int> ret;
    if (StmtToConstTable.count(stmtUsing)==0)
        return ret;
    else return StmtToConstTable.at(stmtUsing);
}


bool ConstTable::HasAnyConst() {
    return !StmtToConstTable.empty();

}

vector<int> ConstTable::GetAllConst() {
    vector<int> listOfConstants;

    for(map<int, vector<int> >::iterator it = StmtToConstTable.begin(); it != StmtToConstTable.end(); it++) {
        for(int i = 0; i < it->second.size(); i++) {
            listOfConstants.push_back(it->second.at(i));
		}
	}

	sort(listOfConstants.begin(), listOfConstants.end());
	
	vector<int>::iterator it;
	it = unique (listOfConstants.begin(), listOfConstants.end()); 
	listOfConstants.resize(distance(listOfConstants.begin(),it) ); // trims excess spaces in vector


    return listOfConstants;
}

int ConstTable::SizeOfConstTable() {
    int sum = 0;

    for(map<int, vector<int> >::iterator it=StmtToConstTable.begin(); it!=StmtToConstTable.end();        it++)
    sum += it->second.size();
    return sum;
}

void ConstTable::ClearData() {
    StmtToConstTable.clear();
    ConstToStmtTable.clear();
}
