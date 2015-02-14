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
	static vector<int> GetAllStmtsOfType(SynonymType type);
	static bool CheckIfStmtOfType(int stmtIndex, SynonymType type);

	//API-PKB and DE
	static void Insert(int stmtIndex, SynonymType type);

	static int GetSize();

	static void ClearData();

private:
	//data structures
	static map<int, SynonymType> indexTypeTable;
	static map<SynonymType, vector<int> > typeIndexTable;
};

#endif
