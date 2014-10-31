#include <utility>
#include <vector>
#include <map>
#include "AST\TNode\TNode.h"
#include "QueryProcessor\Grammar.h"

using namespace std;

class StmtTypeTable {
public:
	StmtTypeTable();

	//API-Query
	vector<int> GetAllStmtsOfType(SynonymType type);
	bool CheckIfStmtOfType(int stmtIndex, SynonymType type);

	//API-PKB and DE
	void insert(int stmtIndex, SynonymType type, TNode node);

private:
	//ds
	map<int, TNode> IndexTNodetable;
	map<SynonymType, int> TypeIndextable;
}