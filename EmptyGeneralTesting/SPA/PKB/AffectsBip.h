#pragma once

#include <vector>

using namespace std;

class AffectsBip {
public:
	AffectsBip();

	// API
	static bool IsAffects(int stmtAffecting, int stmtAffected);
	static vector<int> GetStmtsAffectedBy(int stmtAffecting);
	static vector<int> GetStmtsAffecting(int stmtAffected);

	static bool IsAffectsT(int stmtAffecting, int stmtAffected);
	static vector<int> GetStmtsAffectedTBy(int stmtAffecting);
	static vector<int> GetStmtsAffectingT(int stmtAffected);

};
