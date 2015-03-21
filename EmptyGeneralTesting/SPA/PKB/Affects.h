#pragma once

#include <vector>
#include <queue>

using namespace std;

class Affects {
public:
	Affects(void);

	// API
	static bool IsAffects(int stmtAffecting, int stmtAffected);
	static vector<int> GetStmtsAffectedBy(int stmtAffecting);
	static vector<int> GetStmtsAffecting(int stmtAffected);

	static bool IsAffectsT(int stmtAffecting, int stmtAffected);
	static vector<int> GetStmtsAffectedTBy(int stmtAffecting);
	static vector<int> GetStmtsAffectingT(int stmtAffected);

	~Affects(void);

private:
	static bool CheckCFG(int stmtAffecting, int stmtAffected, int varModified);
	static vector<int> TraverseDownCFG(int stmtAffecting, int varModified);
	//static vector<int> TraverseUpCFG(int stmtAffected, int varModified);
	// may want to add cache here

};

