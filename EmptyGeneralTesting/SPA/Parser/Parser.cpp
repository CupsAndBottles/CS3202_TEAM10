#pragma once

#include "Parser.h"
#include "Tokenizer.h"
#include "Program\Program.h"
#include "Program\TNode\ConstantTNode.h"
#include "QueryProcessor\Grammar.h"
#include "..\AutoTester\source\AbstractWrapper.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void SyntaxError() {
	throw (string) "Syntax error!";
}

Parser::Parser(vector<Token> tokenVector)
	: tokens(tokenVector.begin(), tokenVector.end())
	, currentLineNumber(0) {
}

void Parser::Parse(string fileName) {
	ifstream sourceFile(fileName);
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	sourceFile.close();

	vector<Token> tokens = Tokenizer::Tokenize(buffer.str());
	Parser parser(tokens);
	parser.Parse();
}

Token Parser::ConsumeTopToken() {
	Token token = tokens.front();
	tokens.pop_front();
	return token;
}

Token Parser::PeekAtTopToken() {
	return tokens.front();
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
			return -1;
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
	ProgramTNode& rootNode = Program::GetASTRootNode();

	while (tokens.size() != 0) {
		if (AbstractWrapper::GlobalStop) {
			break;
		}
		ConsumeTopTokenOfType(Token::PROCEDURE);
		Token procedureName = ConsumeTopTokenOfType(Token::IDENTIFIER);
		ProcedureTNode* procedureNode = new ProcedureTNode(procedureName.content);

		StmtListTNode* procedureBody = ParseStmtList("", nullptr);
		procedureNode->SetProcedureBody(procedureBody);
		
		rootNode.AddChild(procedureNode);
	}
}

StmtListTNode* Parser::ParseStmtList(string name, StmtTNode* parent) {
	// first token should be start of stmt list token
	// consumes tokens until a matching close brace is found
	// if tokens are fully consumed, throw exception
	
	ConsumeTopTokenOfType(Token::START_OF_STMT_LIST);

	StmtListTNode* stmtListNode = new StmtListTNode(name);
	StmtTNode* prevStmt = nullptr;
	while (!TopTokenIsType(Token::END_OF_STMT_LIST)) {
		if (AbstractWrapper::GlobalStop) {
			return stmtListNode;
		}

		StmtTNode* stmt = ParseStmt(parent);
		stmtListNode->AddChild(stmt);
		if (prevStmt != nullptr) {
			Follows::SetFollows(prevStmt->GetLineNumber(), stmt->GetLineNumber());
		}
		prevStmt = stmt;
	}

	ConsumeTopTokenOfType(Token::END_OF_STMT_LIST);

	return stmtListNode;
}

StmtTNode* Parser::ParseStmt(StmtTNode* parentStmt) {
	Token firstToken = PeekAtTopToken(); // peek at next token
	StmtTNode* stmt;
	currentLineNumber++;

	if (parentStmt != nullptr) {
		Parent::SetParent(parentStmt->GetLineNumber(), currentLineNumber);
	}

	switch (firstToken.type) {
		case Token::IDENTIFIER:
			stmt = ParseAssignmentStmt();
			ConsumeTopTokenOfType(Token::END_OF_STMT);
			StmtTypeTable::Insert(stmt->GetLineNumber(), ASSIGN);
			break;
		case Token::WHILE:
			stmt = ParseWhileStmt();
			StmtTypeTable::Insert(stmt->GetLineNumber(), WHILE);
			break;
		default:
			SyntaxError();
	}

	if (parentStmt != nullptr) {
		stmt->SetParent(parentStmt);
	}

	Program::InsertStmt(stmt, stmt->GetLineNumber());
	return stmt;
}

AssignmentTNode* Parser::ParseAssignmentStmt() {
	Token varToken = ConsumeTopTokenOfType(Token::IDENTIFIER);
	Token eqToken = ConsumeTopTokenOfType(Token::ASSIGN);

	VariableTNode* LHS = new VariableTNode(varToken.content);
	AssignmentTNode* assignmentStmt = new AssignmentTNode(currentLineNumber);
	Modifies::SetStmtModifiesVar(currentLineNumber, VarTable::InsertVar(varToken.content));
	TNode* RHS = ParseExpr();

	assignmentStmt->BuildAssignmentNode(LHS, RHS);

	return assignmentStmt;
}

TNode* Parser::ParseExpr() {
	Token currentToken = PeekAtTopToken(); // peek
	TNode* result = nullptr;
	while (currentToken.type != Token::END_OF_STMT) {
		if (result == nullptr) {
			result = ParseAtomicToken();

			if (PeekAtTopToken().type == Token::END_OF_STMT) { // peek at next token
				return result;
			}
		}
		result = ParseExpr(result, false);
		currentToken = PeekAtTopToken();
	}
	return result;
}

TNode* Parser::ParseExpr(TNode* LHS, bool isBracket) {
	// if next op is of lower precedence, construct and return
	// if next op is of equal precedence, construct and loop
	// if next op is of higher precedence, perform recursive call
	// if bracket, build bracket and return

	if (PeekAtTopToken().type == Token::END_OF_STMT_LIST) {
		return LHS;
	}
	
	Token op1 = ConsumeTopToken();
	TNode* RHS = ParseAtomicToken();
	Token nextOp = PeekAtTopToken(); // peek
	int comparison = compare(op1.type, nextOp.type);

	if (comparison < 0) { // nextOp is of lower precedence than currentOp
		RHS = ParseExpr(RHS, isBracket);
	}
	BinaryTNode* expression = new BinaryTNode(op1.content);
	expression->BuildBinaryNode(LHS, RHS);
	if (comparison > 0) { // nextOp is of higher precedence than currentOp
		return expression;
	} else { // equal precedence
		return ParseExpr(expression, isBracket);
	}
}

AtomicTNode* Parser::ParseAtomicToken() {
	Token currentToken = ConsumeTopToken(); // peek
	AtomicTNode* result;
	switch (currentToken.type) {
		case Token::IDENTIFIER:
			result = new VariableTNode(currentToken.content);
			Uses::SetStmtUsesVar(currentLineNumber, VarTable::InsertVar(currentToken.content));
			break;
		case Token::NUMBER:
			result = new ConstantTNode(currentToken.content);
			ConstTable::SetStmtUsesConst(currentLineNumber, dynamic_cast<ConstantTNode*>(result)->GetValue());
			break;
		default:
			SyntaxError();
	}

	return result;
}

WhileTNode* Parser::ParseWhileStmt() {
	ConsumeTopTokenOfType(Token::WHILE);

	WhileTNode* whileStmt = new WhileTNode(currentLineNumber);

	// parse condition
	Token condition = ConsumeTopTokenOfType(Token::IDENTIFIER);
	VariableTNode* conditionNode = new VariableTNode(condition.content);
	Uses::SetStmtUsesVar(currentLineNumber, VarTable::InsertVar(condition.content));

	// parse loop body
	StmtListTNode* loopBody = ParseStmtList("", whileStmt);

	// create if statement
	whileStmt->BuildWhileNode(conditionNode, loopBody);
	return whileStmt;
}
//
//void main() {
//	ifstream sourceFile("Parser\sample_SIMPLE_source.txt");
//	stringstream buffer;
//	buffer << sourceFile.rdbuf();
//	sourceFile.close();
//	Program testProgram = Parser::Parse(buffer.str());
//}