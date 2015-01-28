#include <utility>
#include <map>
#include <set>
#include "..\QueryProcessor\Grammar.h"
#include "StmtTypeTable.h"

using namespace std;

map<unsigned int, SynonymType> StmtTypeTable::IndexTypeTable;
map<SynonymType, vector<unsigned int> > StmtTypeTable::TypeIndexTable;

// constructor
StmtTypeTable::StmtTypeTable() {};

vector<unsigned int> StmtTypeTable::GetAllStmtsOfType(SynonymType type) {
	if(type == STMT || type == PROG_LINE)
	{ 
		vector<unsigned int> stmts;
		for(map<unsigned int,SynonymType>::iterator it = IndexTypeTable.begin(); it != IndexTypeTable.end(); ++it)
			stmts.push_back(it->first);

		return stmts;
	}

    else {
		if(TypeIndexTable.find(type) != TypeIndexTable.end())
			return TypeIndexTable.at(type);

		//should throw exception
		else {
			vector<unsigned int> empty;
			return empty;
		}
	}
}

bool StmtTypeTable::CheckIfStmtOfType(unsigned int stmtIndex, SynonymType type) {
	if(type == STMT || type == PROG_LINE) {
		if(IndexTypeTable.at(stmtIndex) == ASSIGN || IndexTypeTable.at(stmtIndex) == WHILE)
			return true;
	}

    return (IndexTypeTable.at(stmtIndex) == type);
}

//API-PKB and DE
void StmtTypeTable::Insert(unsigned int stmtIndex, SynonymType type) {
    IndexTypeTable[stmtIndex] = type;
    TypeIndexTable[type].push_back(stmtIndex);
}

void StmtTypeTable::ClearData()
{
	IndexTypeTable.clear();
	TypeIndexTable.clear();
}
