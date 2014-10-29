//#pragma once
//
//#include "Parser.h"
//#include "PKB.h"
//#include "Tokenizer.h"
//#include "AST/AST.h"
//
//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <deque>
//
//using namespace std;
//
//Token popDeque(deque<Token>& tokenDeque) {
//	Token token = tokenDeque.front();
//	tokenDeque.pop_front();
//	return token;
//}
//
//int Parse (string source) {
//	vector<Token> tokens = Tokenizer::tokenize(source);
//	return Parse(tokens);
//}
//
//int Parse(vector<Token> tokens) {
//	AST ast;
//	vector<ProcedureTNode> procedures;
//	deque<Token> tokenDeque(tokens.get_allocator());
//	while(tokenDeque.size() != 0) {
//		Token procedureHead = popDeque(tokenDeque);
//		StmtListTNode procedureBody = parseStmtList(tokenDeque);
//		procedures.push_back(parseProcedureToken(procedureHead, procedureBody));
//	}
//
//	ProgramTNode program = AST::typecast<ProgramTNode>(AST::CreateTNode(TNode::Program, procedures));
//	ast.InitNewProgram(program);
//
//	// fix return value
//	return 1;
//}
//
//ProcedureTNode parseProcedureToken(Token procedureToken, StmtListTNode procedureBody) {
//	string procedureName = procedureToken.GetContent();
//	ProcedureTNode procedure = AST::AST::typecast<ProcedureTNode>(AST::CreateTNode(TNode::Program, procedures));
//}
//
//StmtListTNode parseStmtList(deque<Token>& tokens) {
//	// first token should be start of stmt list token
//	// consumes tokens until a matching close brace is found
//	// if tokens are fully consumed, throw exception
//	
//}