#pragma once

#include "PKB\Token.h"
#include "Program\Program.h"
#include "Program\TNode\AssignmentTNode.h"
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
	friend class PatternMatcherTest;

public:
	static void Parse(string);
	static int compare(Token::Type, Token::Type);

private:
	Parser(vector<Token>);

	deque<Token> tokens;
	int currentLineNumber;

	Token ConsumeTopToken();
	bool TopTokenIsType(Token::Type);
	void VerifyTopTokenIs(Token::Type);
	Token ConsumeTopTokenOfType(Token::Type);

	void Parse();

	StmtListTNode* ParseStmtList(string, StmtTNode*);
	StmtTNode* ParseStmt();
	StmtTNode* ParseStmt(StmtTNode*);
	AssignmentTNode* ParseAssignmentStmt();
	WhileTNode* ParseWhileStmt();
	TNode* ParseExpr(TNode*, bool);
};
