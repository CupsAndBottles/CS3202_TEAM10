#pragma once

#include "Token.h"
#include "Program\Program.h"
#include "Program\TNode\AssignmentTNode.h"
#include "Program\TNode\CallTNode.h"
#include "Program\TNode\IfTNode.h"
#include "Program\TNode\WhileTNode.h"
#include "PKB\Follows.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "PKB\Parent.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\VarTable.h"

#include <vector>
#include <deque>

using namespace std;

class Parser {
public:
	static Program Parse(string, Follows&, Modifies&, Uses&, Parent&, StmtTypeTable&, VarTable&);
	static int compare(Token::Type, Token::Type);

private:
	Parser(vector<Token>, Follows&, Modifies&, Uses&, Parent&, StmtTypeTable&, VarTable&);

	deque<Token> tokens;
	int currentLineNumber;
	Program program;

	Follows& follows;
	Modifies& modifies;
	Uses& uses;
	Parent& parent;
	StmtTypeTable& stmtTypeTable;
	VarTable& varTable;

	Token ConsumeTopToken();
	bool TopTokenIsType(Token::Type);
	void VerifyTopTokenIs(Token::Type);
	Token ConsumeTopTokenOfType(Token::Type);

	void Parse();

	StmtListTNode* ParseStmtList(string);
	StmtTNode* ParseStmt();
	StmtTNode* ParseStmt(StmtTNode*);
	AssignmentTNode* ParseAssignmentStmt();
	WhileTNode* ParseWhileStmt();
	TNode* ParseExpr(TNode*, bool);
};
