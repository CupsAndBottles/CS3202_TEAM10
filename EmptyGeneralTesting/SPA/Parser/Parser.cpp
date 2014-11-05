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
	vector<Token> tokens = Tokenizer::Tokenize(source);
	Parser parser(tokens);
	parser.Parse();
	return parser.program;
}

Token Parser::ConsumeTopToken() {
	Token token = tokens.front();
	tokens.pop_front();
	return token;
}

bool Parser::TopTokenIsType(Token::Type type) {
	return (tokens.front().type == type);
}

void Parser::VerifyTopTokenIs(Token::Type type) {
	if (!TopTokenIsType(type)) {
		SyntaxError();
	}
}

Token Parser::ConsumeTopTokenOfType(Token::Type type) {
	// verifies that top token is of given type
	// then consumes it
	VerifyTopTokenIs(type);
	return ConsumeTopToken();
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
	ProgramTNode& rootNode = program.GetASTRootNode();

	while(tokens.size() != 0) {
		ConsumeTopTokenOfType(Token::PROCEDURE);
		Token procedureName = ConsumeTopTokenOfType(Token::IDENTIFIER);
		ProcedureTNode* procedureNode = new ProcedureTNode(procedureName.content);

		StmtListTNode* procedureBody = ParseStmtList("");
		procedureNode->SetProcedureBody(procedureBody);
		
		rootNode.AddChild(procedureNode);
	}
}

StmtListTNode* Parser::ParseStmtList(string name) {
	// first token should be start of stmt list token
	// consumes tokens until a matching close brace is found
	// if tokens are fully consumed, throw exception
	
	ConsumeTopTokenOfType(Token::START_OF_STMT_LIST);

	StmtListTNode* stmtListNode = new StmtListTNode(name);
	while (!TopTokenIsType(Token::END_OF_STMT_LIST)) {
		StmtTNode* stmt = ParseStmt();
		stmtListNode->AddChild(stmt);
	}

	ConsumeTopTokenOfType(Token::END_OF_STMT_LIST);

	return stmtListNode;
}

StmtTNode* Parser::ParseStmt(StmtTNode* parentStmt) {
	Token firstToken = tokens.front();
	StmtTNode* stmt;
	currentLineNumber++;

	switch (firstToken.type) {
		case Token::IDENTIFIER:
			stmt = ParseAssignmentStmt();
			ConsumeTopTokenOfType(Token::END_OF_STMT);
			break;
		case Token::WHILE:
			stmt = ParseWhileStmt();
			break;
		default:
			SyntaxError();
	}

	stmt->setParent(parentStmt);
	program.InsertStmt(stmt);
	return stmt;
}

StmtTNode* Parser::ParseStmt() {
	return ParseStmt(nullptr);
}

AssignmentTNode* Parser::ParseAssignmentStmt() {
	Token varToken = ConsumeTopTokenOfType(Token::IDENTIFIER);
	Token eqToken = ConsumeTopTokenOfType(Token::ASSIGN);

	VariableTNode* LHS = new VariableTNode(varToken.content);
	AssignmentTNode* assignmentStmt = new AssignmentTNode(currentLineNumber);
	TNode* RHS = ParseExpr(nullptr, false);

	assignmentStmt->BuildAssignmentNode(LHS, RHS);

	return assignmentStmt;
}

TNode* Parser::ParseExpr(TNode* LHS, bool endOfStmt) {
	// if next op is of lower precedence, construct and return
	// if next op is of equal precedence, construct and loop
	// if next op is of higher precedence, perform recursive call
	// if bracket, build bracket and return

	if (endOfStmt) {
		// base case
		return LHS;
	}

	Token currentToken = ConsumeTopToken();

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
			return ParseExpr(LHS, true);
		} else {
			return ParseExpr(LHS, endOfStmt);
		}

	} else {
		Token currentOp = currentToken;
		currentToken = ConsumeTopToken();
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
			RHS = ParseExpr(RHS, endOfStmt);
		}

		BinaryTNode* expression = new BinaryTNode(currentOp.content);
		expression->BuildBinaryNode(LHS, RHS);
		LHS = expression;
		return ParseExpr(LHS, endOfStmt);
	}
}

WhileTNode* Parser::ParseWhileStmt() {
	ConsumeTopTokenOfType(Token::WHILE);

	WhileTNode* whileStmt = new WhileTNode(currentLineNumber);

	// parse condition
	Token condition = ConsumeTopTokenOfType(Token::IDENTIFIER);
	VariableTNode* conditionNode = new VariableTNode(condition.content);

	// parse loop body
	StmtListTNode* loopBody = ParseStmtList("");

	// create if statement
	whileStmt->BuildWhileNode(conditionNode, loopBody);
	return whileStmt;
}
