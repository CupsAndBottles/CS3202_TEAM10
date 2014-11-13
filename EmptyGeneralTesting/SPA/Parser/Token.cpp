#pragma once

#include "Token.h"

#include <iostream>

using namespace std;

const string Token::StartOfStmtList		= "{";
const string Token::EndOfStmtList		= "}";
const string Token::EndOfStmt			= ";";

const string Token::OperatorPlus		= "+";
const string Token::OperatorAssign		= "=";

const string Token::KeywordWhile		= "while";
const string Token::KeywordProcedure	= "procedure";

Token& Token::operator=(const Token& element) {
	content = element.content;
	type = element.type;
	return *this;
}

Token::Token(string content, Type type) : content(content), type(type) {}