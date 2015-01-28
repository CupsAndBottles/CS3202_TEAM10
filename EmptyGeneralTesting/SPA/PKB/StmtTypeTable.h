#ifndef STMTTYPETABLE_H
#define STMTTYPETABLE_H

#include <utility>
#include <vector>
#include <map>
#include <set>

#include "..\QueryProcessor\Grammar.h"

using namespace std;

class StmtTypeTable {
public:
	StmtTypeTable();

	//API-Query
	static vector<unsigned int> GetAllStmtsOfType(SynonymType type);
	static bool CheckIfStmtOfType(unsigned int stmtIndex, SynonymType type);

	//API-PKB and DE
	static void Insert(unsigned int stmtIndex, SynonymType type);

	static void ClearData();

private:
	//data structures
	static map<unsigned int, SynonymType> IndexTypeTable;
	static map<SynonymType, vector<unsigned int> > TypeIndexTable;
};

#endif
