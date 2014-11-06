#include <utility>
#include <map>
#include <set>
#include "QueryProcessor/Grammar.h"
#include "StmtTypeTable.h"

using namespace std;

map<int, SynonymType> StmtTypeTable::IndexTypeTable;
map<SynonymType, set<int> > StmtTypeTable::TypeIndexTable;

// constructor
StmtTypeTable::StmtTypeTable() {

};

set<int> StmtTypeTable::GetAllStmtsOfType(SynonymType type) {
    return TypeIndexTable.at(type);
}

bool StmtTypeTable::CheckIfStmtOfType(int stmtIndex, SynonymType type) {
    return (IndexTypeTable.at(stmtIndex) == type);
}

//API-PKB and DE
void StmtTypeTable::insert(int stmtIndex, SynonymType type) {
    IndexTypeTable[stmtIndex] = type;
    TypeIndexTable[type].insert(stmtIndex);
}

