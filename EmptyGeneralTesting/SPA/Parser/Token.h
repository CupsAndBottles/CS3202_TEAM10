#pragma once

#include <iostream>

using namespace std;

class Token {
public:
	static const string StartOfStmtList;
	static const string EndOfStmtList;
	static const string EndOfStmt;

	static const string OperatorPlus;
	static const string OperatorAssign;

	static const string KeywordWhile;
	static const string KeywordProcedure;

	enum Type {
		START_OF_STMT_LIST = 0,
		END_OF_STMT_LIST,
		END_OF_STMT,
		PLUS,
		ASSIGN,
		WHILE,
		PROCEDURE,
		NUMBER,
		IDENTIFIER,
		NONTOKEN
	};


	Token& operator=(const Token& element);

	Token(string content, Type type);

	Type type;
	string content;

private:

};