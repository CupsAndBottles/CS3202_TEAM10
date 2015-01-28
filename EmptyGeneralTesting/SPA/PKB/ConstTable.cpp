#include <utility>
#include <map>
#include <vector>
#include "ConstTable.h"
#include "Parent.h"

using namespace std;

map <unsigned int, vector<unsigned int> > ConstTable::StmtToConstTable;
map <unsigned int, vector<unsigned int> > ConstTable::ConstToStmtTable;

// empty constructor
ConstTable::ConstTable() {}

// API
void ConstTable::SetStmtUsesConst(unsigned int stmtUsing, unsigned int constUsed) {
    if (!IsStmtUsingConst(stmtUsing, constUsed)) {
        StmtToConstTable[stmtUsing].push_back(constUsed);
        ConstToStmtTable[constUsed].push_back(stmtUsing);
    }

    if (Parent::GetParentOf(stmtUsing) != -1)
        SetStmtUsesConst(Parent::GetParentOf(stmtUsing), constUsed);
}

bool ConstTable::IsStmtUsingConst(unsigned int stmtUsing, unsigned int constUsed) {
    if (StmtToConstTable.count(stmtUsing)!=0)
        for (unsigned int i=0; i<StmtToConstTable.at(stmtUsing).size(); i++)
            if (StmtToConstTable.at(stmtUsing).at(i) == constUsed)
                return true;
    return false;
}

vector<unsigned int> ConstTable::GetStmtUsingConst(unsigned int constUsed) {
    vector<unsigned int> ret;
    if (ConstToStmtTable.count(constUsed)==0)
        return ret;
    else return ConstToStmtTable.at(constUsed);
}

vector<unsigned int> ConstTable::GetConstUsedByStmt(unsigned int stmtUsing) {
    vector<unsigned int> ret;
    if (StmtToConstTable.count(stmtUsing)==0)
        return ret;
    else return StmtToConstTable.at(stmtUsing);
}


bool ConstTable::HasAnyConst() {
    return !StmtToConstTable.empty();

}

vector<unsigned int> ConstTable::GetAllConst() {
    vector<unsigned int> ret;

    for(map<unsigned int, vector<unsigned int> >::iterator it=StmtToConstTable.begin(); it!=StmtToConstTable.end(); it++)
        for(unsigned int i=0; i<it->second.size(); i++)
            ret.push_back(it->second.at(i));

    return ret;
}

unsigned int ConstTable::SizeOfConstTable() {
    unsigned int sum = 0;

    for(map<unsigned int, vector<unsigned int> >::iterator it=StmtToConstTable.begin(); it!=StmtToConstTable.end();        it++)
    sum += it->second.size();
    return sum;
}

void ConstTable::ClearData() 
{
    StmtToConstTable.clear();
    ConstToStmtTable.clear();
}
