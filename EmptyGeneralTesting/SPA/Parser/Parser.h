#pragma once

#include "Token.h"
#include "..\Program\Program.h"
#include "..\PKB\Follows.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Uses.h"
#include "..\PKB\Parent.h"
#include "..\PKB\StmtTypeTable.h"
#include "..\PKB\VarTable.h"
#include "..\PKB\ConstTable.h"

#include <vector>
#include <deque>

using namespace std;

class Parser {
	friend class PatternMatcherTest;

public:
	static void Parse(string);
	static unsigned int compare(Token::Type, Token::Type);

protected:
	Parser(vector<Token>);

	deque<Token> tokens;
	unsigned int currentLineNumber;

	Token ConsumeTopToken();
	Token PeekAtTopToken();
	bool TopTokenIsType(Token::Type);
	void VerifyTopTokenIs(Token::Type);
	Token ConsumeTopTokenOfType(Token::Type);

	void Parse();

	TNode* ParseStmtList(string, TNode*);
	TNode* ParseStmt();
	TNode* ParseStmt(TNode*);
	TNode* ParseAssignmentStmt();
	TNode* ParseWhileStmt();
	TNode* ParseExpr();
	TNode* ParseExpr(TNode*, bool);
	TNode* ParseAtomicToken();
};
