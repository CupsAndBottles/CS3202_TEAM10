#include <utility>
#include <map>
#include <set>
#include "..\QueryProcessor\Grammar.h"
#include "StmtTypeTable.h"

using namespace std;

map<int, SynonymType> StmtTypeTable::indexTypeTable;
map<SynonymType, vector<int> > StmtTypeTable::typeIndexTable;

// constructor
StmtTypeTable::StmtTypeTable() {};

vector<int> StmtTypeTable::GetAllStmtsOfType(SynonymType type) {
	if(type == STMT || type == PROG_LINE) { 
		vector<int> stmts;
		for(map<int,SynonymType>::iterator it = indexTypeTable.begin(); it != indexTypeTable.end(); ++it)
			stmts.push_back(it->first);

		return stmts;
	}

    else {
		if(typeIndexTable.find(type) != typeIndexTable.end())
			return typeIndexTable.at(type);

		//should throw exception
		else {
			vector<int> empty;
			return empty;
		}
	}
}

bool StmtTypeTable::CheckIfStmtOfType(int stmtIndex, SynonymType type) {
	if(type == STMT || type == PROG_LINE) {
		if(indexTypeTable.at(stmtIndex) == ASSIGN || indexTypeTable.at(stmtIndex) == WHILE)
			return true;
	}

    return (indexTypeTable.at(stmtIndex) == type);
}

//API-PKB and DE
void StmtTypeTable::Insert(int stmtIndex, SynonymType type) {
    indexTypeTable[stmtIndex] = type;
    typeIndexTable[type].push_back(stmtIndex);
}

int StmtTypeTable::GetNoOfStmts() {
	return typeIndexTable.size();
}

void StmtTypeTable::ClearData() {
	indexTypeTable.clear();
	typeIndexTable.clear();
}
