#pragma once

#include "Parser.h"
#include "Tokenizer.h"
#include "..\Program\Program.h"
#include "..\Program\TNode\TNode.h"
#include "..\QueryProcessor\Grammar.h"
#include "..\..\AutoTester\source\AbstractWrapper.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void SyntaxError() {
	throw (string) "Syntax error!";
}

TNode* ConstructIfTNode(int lineNumber) {
	return new TNode(TNode::ConstructIfTNode(lineNumber));
}

TNode* ConstructWhileTNode(int lineNumber) {
	return new TNode(TNode::ConstructWhileTNode(lineNumber));
}

TNode* ConstructCallTNode(int lineNumber) {
	return new TNode(TNode::ConstructCallTNode(lineNumber));
}

TNode* ConstructAssignmentTNode(int lineNumber) {
	return new TNode(TNode::ConstructAssignmentTNode(lineNumber));
}

TNode* ConstructConstTNode(string value) {
	return new TNode(TNode::ConstructConstTNode(value));
}

TNode* ConstructVarTNode(string symbol) {
	return new TNode(TNode::ConstructVarTNode(symbol));
}

TNode* ConstructOperatorTNode(string symbol) {
	return new TNode(TNode::ConstructOperatorTNode(symbol));
}

TNode* ConstructStmtListTNode(string name) {
	return new TNode(TNode::ConstructStmtListTNode(name));
}

TNode* ConstructProcedureTNode(string name) {
	return new TNode(TNode::ConstructProcedureTNode(name));
}

TNode* ConstructStmtTNode(TNode::Type type, int lineNumber) {
	return new TNode(TNode::ConstructStmtTNode(type, lineNumber));
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

unsigned int getPrecedenceValue(Token::Type type) {
	switch (type) {
		case Token::END_OF_STMT:
			return -1;
		case Token::PLUS:
			return 1;
		default:
			SyntaxError();
	}
}

unsigned int Parser::compare(Token::Type first, Token::Type second) {
	unsigned int valFirst = getPrecedenceValue(first);
	unsigned int valSecond = getPrecedenceValue(second);
	return (valFirst - valSecond);
}

void Parser::Parse() {
	TNode& rootNode = Program::GetASTRootNode();

	while (tokens.size() != 0) {
		if (AbstractWrapper::GlobalStop) {
			break;
		}
		ConsumeTopTokenOfType(Token::PROCEDURE);
		Token procedureName = ConsumeTopTokenOfType(Token::IDENTIFIER);
		TNode* procedureNode = ConstructProcedureTNode(procedureName.content);

		TNode* procedureBody = ParseStmtList("", nullptr);
		procedureNode->AddChild(procedureBody);
		
		rootNode.AddChild(procedureNode);
	}
}

TNode* Parser::ParseStmtList(string name, TNode* parent) {
	// first token should be start of stmt list token
	// consumes tokens until a matching close brace is found
	// if tokens are fully consumed, throw exception
	
	ConsumeTopTokenOfType(Token::START_OF_STMT_LIST);

	TNode* stmtListNode = ConstructStmtListTNode("");
	TNode* prevStmt = nullptr;
	while (!TopTokenIsType(Token::END_OF_STMT_LIST)) {
		if (AbstractWrapper::GlobalStop) {
			return stmtListNode;
		}

		TNode* stmt = ParseStmt(parent);
		stmtListNode->AddChild(stmt);
		if (prevStmt != nullptr) {
			Follows::SetFollows(prevStmt->GetLineNumber(), stmt->GetLineNumber());
		}
		prevStmt = stmt;
	}

	ConsumeTopTokenOfType(Token::END_OF_STMT_LIST);

	return stmtListNode;
}

TNode* Parser::ParseStmt(TNode* parentStmt) {
	Token firstToken = PeekAtTopToken(); // peek at next token
	TNode* stmt;
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
		stmt->SetLogicalParent(parentStmt);
	}

	Program::InsertStmt(stmt, stmt->GetLineNumber());
	return stmt;
}

TNode* Parser::ParseAssignmentStmt() {
	Token varToken = ConsumeTopTokenOfType(Token::IDENTIFIER);
	Token eqToken = ConsumeTopTokenOfType(Token::ASSIGN);

	TNode* LHS = ConstructVarTNode(varToken.content);
	TNode* assignmentStmt = ConstructAssignmentTNode(currentLineNumber);
	Modifies::SetStmtModifiesVar(currentLineNumber, VarTable::InsertVar(varToken.content));
	TNode* RHS = ParseExpr();

	assignmentStmt->AddChild(LHS);
	assignmentStmt->AddChild(RHS);

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
	unsigned int comparison = compare(op1.type, nextOp.type);

	if (comparison < 0) { // nextOp is of lower precedence than currentOp
		RHS = ParseExpr(RHS, isBracket);
	}
	TNode* expression = ConstructOperatorTNode(op1.content);
	expression->AddChild(LHS);
	expression->AddChild(RHS);
	if (comparison > 0) { // nextOp is of higher precedence than currentOp
		return expression;
	} else { // equal precedence
		return ParseExpr(expression, isBracket);
	}
}

TNode* Parser::ParseAtomicToken() {
	Token currentToken = ConsumeTopToken(); // peek
	TNode* result;
	switch (currentToken.type) {
		case Token::IDENTIFIER:
			result = ConstructVarTNode(currentToken.content);
			Uses::SetStmtUsesVar(currentLineNumber, VarTable::InsertVar(currentToken.content));
			break;
		case Token::NUMBER:
			result = ConstructConstTNode(currentToken.content);
			ConstTable::SetStmtUsesConst(currentLineNumber, stoi(result->GetContent()));
			break;
		default:
			SyntaxError();
	}

	return result;
}

TNode* Parser::ParseWhileStmt() {
	ConsumeTopTokenOfType(Token::WHILE);

	TNode* whileStmt = ConstructWhileTNode(currentLineNumber);

	// parse condition
	Token condition = ConsumeTopTokenOfType(Token::IDENTIFIER);
	TNode* conditionNode = ConstructVarTNode(condition.content);
	Uses::SetStmtUsesVar(currentLineNumber, VarTable::InsertVar(condition.content));

	// parse loop body
	TNode* loopBody = ParseStmtList("", whileStmt);

	// create while statement
	whileStmt->AddChild(conditionNode);
	whileStmt->AddChild(loopBody);
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