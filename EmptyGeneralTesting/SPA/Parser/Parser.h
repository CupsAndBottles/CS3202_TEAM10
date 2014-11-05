#pragma once

#include "Token.h"
#include "Program\Program.h"
#include "Program\TNode\AssignmentTNode.h"
#include "Program\TNode\CallTNode.h"
#include "Program\TNode\IfTNode.h"
#include "Program\TNode\WhileTNode.h"

#include <vector>
#include <deque>

using namespace std;

class Parser {
public:
	static Program Parse(string);
	static int compare(Token::Type, Token::Type);

private:
	Parser(vector<Token>);

	deque<Token> tokens;
	int currentLineNumber;

	Token consumeTopToken();
	bool topTokenIsType(Token::Type);
	void verifyTopTokenIs(Token::Type);
	Token consumeTopTokenOfType(Token::Type);

	Program Parse();

	StmtListTNode* parseStmtList(string);
	StmtTNode* parseStmt();
	StmtTNode* parseStmt(StmtTNode*);
	AssignmentTNode* parseAssignmentStmt();
	WhileTNode* parseWhileStmt();
	IfTNode* parseIfStmt();
	CallTNode* parseCallStmt();
	TNode* parseExpr(TNode*, int, bool);
};
