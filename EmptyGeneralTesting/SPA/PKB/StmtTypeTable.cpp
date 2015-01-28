#include <utility>
#include <map>
#include <set>
#include "..\QueryProcessor\Grammar.h"
#include "StmtTypeTable.h"

using namespace std;

map<int, SynonymType> StmtTypeTable::IndexTypeTable;
map<SynonymType, vector<int> > StmtTypeTable::TypeIndexTable;

// constructor
StmtTypeTable::StmtTypeTable() {};

vector<int> StmtTypeTable::GetAllStmtsOfType(SynonymType type) {
	if(type == STMT || type == PROG_LINE)
	{ 
		vector<int> stmts;
		for(map<int,SynonymType>::iterator it = IndexTypeTable.begin(); it != IndexTypeTable.end(); ++it)
			stmts.push_back(it->first);

		return stmts;
	}

    else {
		if(TypeIndexTable.find(type) != TypeIndexTable.end())
			return TypeIndexTable.at(type);

		//should throw exception
		else {
			vector<int> empty;
			return empty;
		}
	}
}

bool StmtTypeTable::CheckIfStmtOfType(int stmtIndex, SynonymType type) {
	if(type == STMT || type == PROG_LINE) {
		if(IndexTypeTable.at(stmtIndex) == ASSIGN || IndexTypeTable.at(stmtIndex) == WHILE)
			return true;
	}

    return (IndexTypeTable.at(stmtIndex) == type);
}

//API-PKB and DE
void StmtTypeTable::Insert(int stmtIndex, SynonymType type) {
    IndexTypeTable[stmtIndex] = type;
    TypeIndexTable[type].push_back(stmtIndex);
}

void StmtTypeTable::ClearData()
{
	IndexTypeTable.clear();
	TypeIndexTable.clear();
}
