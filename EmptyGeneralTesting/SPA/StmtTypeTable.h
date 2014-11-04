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
	void insert(int stmtIndex, SynonymType type);

private:
	//data structures
	map<int, SynonymType> IndexTypeTable;
	map<SynonymType, set<int> > TypeIndexTable;
};
