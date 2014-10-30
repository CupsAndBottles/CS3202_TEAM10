#include <utility>
#include <vector>
#include "Grammar.h"
#include "TNode.h"

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