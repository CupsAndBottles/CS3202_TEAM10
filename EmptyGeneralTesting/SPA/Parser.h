#pragma once

#include "Token.h"
#include "AST\AST.h"
#include "AST\TNode\AssignmentTNode.h"
#include "AST\TNode\CallTNode.h"
#include "AST\TNode\IfTNode.h"
#include "AST\TNode\WhileTNode.h"

#include <vector>
#include <deque>

using namespace std;

class Parser {
public:
	static AST Parse(string);
	static int compare(Token::Type, Token::Type);

private:
	Parser(vector<Token>);

	deque<Token> tokens;
	int currentLineNumber;

	Token consumeTopToken();
	bool topTokenIsType(Token::Type);
	void verifyTopTokenIs(Token::Type);
	Token consumeTopTokenOfType(Token::Type);

	AST Parse();

	StmtListTNode parseStmtList(string);
	StmtTNode parseStmt();
	StmtTNode parseStmt(StmtTNode*);
	AssignmentTNode parseAssignmentStmt();
	WhileTNode parseWhileStmt();
	IfTNode parseIfStmt();
	CallTNode parseCallStmt();
	TNode parseExpr(TNode*, int, bool);
};
