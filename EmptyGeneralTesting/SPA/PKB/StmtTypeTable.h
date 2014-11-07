#ifndef STMTTYPETABLE_H
#define STMTTYPETABLE_H

#include <utility>
#include <vector>
#include <map>
#include <set>

#include "QueryProcessor/Grammar.h"

using namespace std;

class StmtTypeTable {
public:
	StmtTypeTable();

	//API-Query
	static set<int> GetAllStmtsOfType(SynonymType type);
	static bool CheckIfStmtOfType(int stmtIndex, SynonymType type);

	//API-PKB and DE
	static void insert(int stmtIndex, SynonymType type);

private:
	//data structures
	static map<int, SynonymType> IndexTypeTable;
	static map<SynonymType, set<int> > TypeIndexTable;
};

#endif