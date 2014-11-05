#pragma once

#include <vector>

using namespace std;

class CFGNode {
public:
	const int stmtNumber;

	CFGNode(int);
	const CFGNode* nextStmt();
	const CFGNode* chooseOption(int);
	void addOption(CFGNode*);
	
private:
	vector<const CFGNode*> children;

};