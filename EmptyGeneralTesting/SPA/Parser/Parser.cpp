#pragma once

#include "Parser.h"
#include "Tokenizer.h"
#include "Program/Program.h"
#include "Program/TNode/ConstantTNode.h"

#include <iostream>

using namespace std;

void SyntaxError() {
	throw (string) "Syntax error!";
}

Parser::Parser(vector<Token> tokenVector) 
	: tokens(tokenVector.begin(), tokenVector.end()) 
	, currentLineNumber(0) {
}

Program Parser::Parse (string source) {
	vector<Token> tokens = Tokenizer::tokenize(source);
	Parser parser(tokens);
	parser.Parse();
	return parser.program;
}

Token Parser::consumeTopToken() {
	Token token = tokens.front();
	tokens.pop_front();
	return token;
}

bool Parser::topTokenIsType(Token::Type type) {
	return (tokens.front().type == type);
}

void Parser::verifyTopTokenIs(Token::Type type) {
	if (!topTokenIsType(type)) {
		SyntaxError();
	}
}

Token Parser::consumeTopTokenOfType(Token::Type type) {
	// verifies that top token is of given type
	// then consumes it
	verifyTopTokenIs(type);
	return consumeTopToken();
}

int getPrecedenceValue(Token::Type type) {
	switch (type) {
		case Token::END_OF_STMT:
			return 0;
		case Token::PLUS:
			return 1;
		default:
			SyntaxError();
	}
}

int Parser::compare(Token::Type first, Token::Type second) {
	int valFirst = getPrecedenceValue(first);
	int valSecond = getPrecedenceValue(second);
	return (valFirst - valSecond);
}

void Parser::Parse() {
	ProgramTNode& rootNode = program.getASTRootNode();

	while(tokens.size() != 0) {
		consumeTopTokenOfType(Token::PROCEDURE);
		Token procedureName = consumeTopTokenOfType(Token::IDENTIFIER);
		ProcedureTNode* procedureNode = new ProcedureTNode(procedureName.content);

		StmtListTNode* procedureBody = parseStmtList("");
		procedureNode->setProcedureBody(procedureBody);
		
		rootNode.addChild(procedureNode);
	}
}

StmtListTNode* Parser::parseStmtList(string name) {
	// first token should be start of stmt list token
	// consumes tokens until a matching close brace is found
	// if tokens are fully consumed, throw exception
	
	consumeTopTokenOfType(Token::START_OF_STMT_LIST);

	StmtListTNode* stmtListNode = new StmtListTNode(name);
	while (!topTokenIsType(Token::END_OF_STMT_LIST)) {
		StmtTNode* stmt = parseStmt();
		stmtListNode->addChild(stmt);
	}

	consumeTopTokenOfType(Token::END_OF_STMT_LIST);

	return stmtListNode;
}

StmtTNode* Parser::parseStmt(StmtTNode* parentStmt) {
	Token firstToken = tokens.front();
	StmtTNode* stmt;
	currentLineNumber++;

	switch (firstToken.type) {
		case Token::IDENTIFIER:
			stmt = parseAssignmentStmt();
			consumeTopTokenOfType(Token::END_OF_STMT);
			break;
		case Token::WHILE:
			stmt = parseWhileStmt();
			break;
		default:
			SyntaxError();
	}

	stmt->setParent(parentStmt);
	program.insertStmt(stmt);
	return stmt;
}

StmtTNode* Parser::parseStmt() {
	return parseStmt(nullptr);
}

AssignmentTNode* Parser::parseAssignmentStmt() {
	Token varToken = consumeTopTokenOfType(Token::IDENTIFIER);
	Token eqToken = consumeTopTokenOfType(Token::ASSIGN);

	VariableTNode* LHS = new VariableTNode(varToken.content);
	AssignmentTNode* assignmentStmt = new AssignmentTNode(currentLineNumber);
	TNode* RHS = parseExpr(nullptr, false);

	assignmentStmt->buildAssignmentNode(LHS, RHS);

	return assignmentStmt;
}

TNode* Parser::parseExpr(TNode* LHS, bool endOfStmt) {
	// if next op is of lower precedence, construct and return
	// if next op is of equal precedence, construct and loop
	// if next op is of higher precedence, perform recursive call
	// if bracket, build bracket and return

	if (endOfStmt) {
		// base case
		return LHS;
	}

	Token currentToken = consumeTopToken();

	if (LHS == nullptr) {
		switch (currentToken.type) {
			case Token::IDENTIFIER:
				LHS = new VariableTNode(currentToken.content);
				break;
			case Token::NUMBER:
				LHS = new ConstantTNode(currentToken.content);
				break;
			default:
				SyntaxError();
		}

		if (tokens[0].type == Token::END_OF_STMT) { // peek at next token
			return parseExpr(LHS, true);
		} else {
			return parseExpr(LHS, endOfStmt);
		}

	} else {
		Token currentOp = currentToken;
		currentToken = consumeTopToken();
		TNode* RHS;
		switch (currentToken.type) {
			case Token::IDENTIFIER:
				RHS = new VariableTNode(currentToken.content);
				break;
			case Token::NUMBER:
				RHS = new ConstantTNode(currentToken.content);
				break;
			default:
				SyntaxError();
		}
		Token nextOp = tokens[0]; // peek
		int comparison = compare(currentOp.type, nextOp.type);
		if (nextOp.type == Token::END_OF_STMT) {
			endOfStmt = true;
		}

		if (comparison > 0) { // nextOp is of higher precedence than currentOp
			RHS = parseExpr(RHS, endOfStmt);
		}

		BinaryTNode* expression = new BinaryTNode(currentOp.content);
		expression->buildBinaryNode(LHS, RHS);
		LHS = expression;
		return parseExpr(LHS, endOfStmt);
	}
}

WhileTNode* Parser::parseWhileStmt() {
	consumeTopTokenOfType(Token::WHILE);

	WhileTNode* whileStmt = new WhileTNode(currentLineNumber);

	// parse condition
	Token condition = consumeTopTokenOfType(Token::IDENTIFIER);
	VariableTNode* conditionNode = new VariableTNode(condition.content);

	// parse loop body
	StmtListTNode* loopBody = parseStmtList("");

	// create if statement
	whileStmt->buildWhileTNode(conditionNode, loopBody);
	return whileStmt;
}
