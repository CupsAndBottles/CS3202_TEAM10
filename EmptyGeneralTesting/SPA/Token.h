#pragma once

#include <iostream>

using namespace std;

class Token {
public:
	static const string START_OF_STMT_LIST;
	static const string END_OF_STMT_LIST;
	static const string OPEN_BRACE;
	static const string CLOSE_BRACE;
	static const string END_OF_STMT;

	static const string OPERATOR_PLUS;
	static const string OPERATOR_MINUS;
	static const string OPERATOR_MULTIPLY;
	static const string OPERATOR_ASSIGN;

	static const string KEYWORD_CALL;
	static const string KEYWORD_WHILE;
	static const string KEYWORD_IF;
	static const string KEYWORD_THEN;
	static const string KEYWORD_ELSE;
	static const string KEYWORD_PROCEDURE;

	static const string NEWLINE_WIN;
	static const string NEWLINE_UNIX;

	enum Type {
		StartOfStmtList,
		EndOfStmtList,
		EndOfStmt,
		OpenBrace,
		CloseBrace,
		Plus,
		Minus,
		Multiply,
		Assign,
		Call,
		While,
		If,
		Then,
		Else,
		Procedure,
		Newline,
		Number,
		Identifier,
		Nontoken
	};

	Token(string content, Type type);

	Type GetType();
	string GetContent();

private:
	const Type type;
	const string content;

	Token() {};

};