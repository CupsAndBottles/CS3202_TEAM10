#pragma once

#include "Parser.h"
#include "PKB.h"
#include "Tokenizer.h"
#include "AST/AST.h"
#include "AST/TNode/ConstantTNode.h"

#include <iostream>

using namespace std;

void SyntaxError() {
	throw (string) "Syntax error!";
}

Parser::Parser(vector<Token> tokenVector) 
	: tokens(tokenVector.begin(), tokenVector.end()) 
	, currentLineNumber(0) {
}

AST Parser::Parse (string source) {
	vector<Token> tokens = Tokenizer::tokenize(source);
	return Parser(tokens).Parse();
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
		case Token::CloseBrace:
			// fallthrough
		case Token::EndOfStmt:
			return 0;
		case Token::Plus:
			// fallthrough
		case Token::Minus:
			return 1;
		case Token::Multiply:
			return 2;
		default:
			SyntaxError();
	}
}

int Parser::compare(Token::Type first, Token::Type second) {
	int valFirst = getPrecedenceValue(first);
	int valSecond = getPrecedenceValue(second);
	return (valFirst - valSecond);
}

AST Parser::Parse() {
	AST ast;
	ProgramTNode& rootNode = ast.getRootNode();

	while(tokens.size() != 0) {
		consumeTopTokenOfType(Token::Procedure);
		Token procedureName = consumeTopTokenOfType(Token::Identifier);
		ProcedureTNode* procedureNode = new ProcedureTNode(procedureName.content);

		StmtListTNode* procedureBody = parseStmtList("");
		procedureNode->setProcedureBody(procedureBody);
		
		rootNode.addChild(procedureNode);
	}

	return ast;
}

StmtListTNode* Parser::parseStmtList(string name) {
	// first token should be start of stmt list token
	// consumes tokens until a matching close brace is found
	// if tokens are fully consumed, throw exception
	
	consumeTopTokenOfType(Token::StartOfStmtList);

	StmtListTNode* stmtListNode = new StmtListTNode(name);
	while (!topTokenIsType(Token::EndOfStmtList)) {
		StmtTNode* stmt = parseStmt();
		stmtListNode->addChild(stmt);
	}

	consumeTopTokenOfType(Token::EndOfStmtList);

	return stmtListNode;
}

StmtTNode* Parser::parseStmt(StmtTNode* parentStmt) {
	Token firstToken = tokens.front();
	StmtTNode* stmt;
	currentLineNumber++;

	switch (firstToken.type) {
		case Token::Identifier:
			stmt = parseAssignmentStmt();
			consumeTopTokenOfType(Token::EndOfStmt);
			break;
		case Token::Call:
			stmt = parseCallStmt();
			consumeTopTokenOfType(Token::EndOfStmt);
			break;
		case Token::While:
			stmt = parseWhileStmt();
			break;
		case Token::If:
			stmt = parseIfStmt();
			break;
		default:
			SyntaxError();
	}

	stmt->setParent(parentStmt);
	return stmt;
}

StmtTNode* Parser::parseStmt() {
	return parseStmt(nullptr);
}

AssignmentTNode* Parser::parseAssignmentStmt() {
	Token varToken = consumeTopTokenOfType(Token::Identifier);
	Token eqToken = consumeTopTokenOfType(Token::Assign);

	VariableTNode* LHS = new VariableTNode(varToken.content);
	AssignmentTNode* assignmentStmt = new AssignmentTNode(currentLineNumber);
	TNode* RHS = parseExpr(nullptr, 0, false);

	assignmentStmt->buildAssignmentNode(LHS, RHS);

	return assignmentStmt;
}

TNode* Parser::parseExpr(TNode* LHS, int bracketCounter, bool endOfStmt) {
	// if next op is of lower precedence, construct and return
	// if next op is of equal precedence, construct and loop
	// if next op is of higher precedence, perform recursive call
	// if bracket, build bracket and return

	if (bracketCounter == 0 && endOfStmt) {
		// base case
		return LHS;
	}

	Token currentToken = consumeTopToken();

	if (LHS == nullptr) {
		switch (currentToken.type) {
			case Token::Identifier:
				LHS = new VariableTNode(currentToken.content);
				break;
			case Token::Number:
				LHS = new ConstantTNode(currentToken.content);
				break;
			case Token::OpenBrace:
				LHS = parseExpr(nullptr, 1, true);
				break;
			default:
				SyntaxError();
		}

		if (tokens[0].type == Token::EndOfStmt) { // peek at next token
			return parseExpr(LHS, bracketCounter, true);
		} else {
			return parseExpr(LHS, bracketCounter, endOfStmt);
		}

	} else {
		Token currentOp = currentToken;
		currentToken = consumeTopToken();
		TNode* RHS;
		switch (currentToken.type) {
			case Token::Identifier:
				RHS = new VariableTNode(currentToken.content);
				break;
			case Token::Number:
				RHS = new ConstantTNode(currentToken.content);
				break;
			case Token::OpenBrace:
				RHS = parseExpr(nullptr, 1, true);
				break;
			default:
				SyntaxError();
		}
		Token nextOp = tokens[0]; // peek
		int comparison = compare(currentOp.type, nextOp.type);
		if (nextOp.type == Token::CloseBrace) {
			consumeTopToken(); // remove close brace
			bracketCounter--;
		} else if (nextOp.type == Token::EndOfStmt) {
			endOfStmt = true;
		}

		if (comparison > 0) { // nextOp is of higher precedence than currentOp
			RHS = parseExpr(RHS, bracketCounter, endOfStmt);
		}

		BinaryTNode* expression = new BinaryTNode(currentOp.content);
		expression->buildBinaryNode(LHS, RHS);
		LHS = expression;
		return parseExpr(LHS, bracketCounter, endOfStmt);
	}
}

CallTNode* Parser::parseCallStmt() {
	consumeTopTokenOfType(Token::Call);
	Token procedureName = consumeTopTokenOfType(Token::Identifier);
	CallTNode* stmt = new CallTNode(currentLineNumber, procedureName.content);
	return stmt;
}

IfTNode* Parser::parseIfStmt() {
	consumeTopTokenOfType(Token::While);

	IfTNode* ifStmt = new IfTNode(currentLineNumber);

	// parse condition
	Token condition = consumeTopTokenOfType(Token::Identifier);
	VariableTNode* conditionNode = new VariableTNode(condition.content);

	// parse then branch
	Token thenToken = consumeTopTokenOfType(Token::Then);
	StmtListTNode* thenBranch = parseStmtList(thenToken.content);

	// parse else branch
	Token elseToken = consumeTopTokenOfType(Token::Else);
	StmtListTNode* elseBranch = parseStmtList(elseToken.content);

	// create if statement
	ifStmt->buildIfTNode(conditionNode, thenBranch, elseBranch);
	return ifStmt;
}

WhileTNode* Parser::parseWhileStmt() {
	consumeTopTokenOfType(Token::While);

	WhileTNode* whileStmt = new WhileTNode(currentLineNumber);

	// parse condition
	Token condition = consumeTopTokenOfType(Token::Identifier);
	VariableTNode* conditionNode = new VariableTNode(condition.content);

	// parse loop body
	StmtListTNode* loopBody = parseStmtList("");

	// create if statement
	whileStmt->buildWhileTNode(conditionNode, loopBody);
	return whileStmt;
}