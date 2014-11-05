#pragma once

#include "Token.h"

#include <iostream>

using namespace std;

const string Token::START_OF_STMT_LIST	= "{";
const string Token::END_OF_STMT_LIST	= "}";
const string Token::OPEN_BRACE			= "(";
const string Token::CLOSE_BRACE			= ")";
const string Token::END_OF_STMT			= ";";

const string Token::OPERATOR_PLUS		= "+";
const string Token::OPERATOR_MINUS		= "-";
const string Token::OPERATOR_MULTIPLY	= "*";
const string Token::OPERATOR_ASSIGN		= "=";

const string Token::KEYWORD_CALL		= "call";
const string Token::KEYWORD_WHILE		= "while";
const string Token::KEYWORD_IF			= "if";
const string Token::KEYWORD_THEN		= "then";
const string Token::KEYWORD_ELSE		= "else";
const string Token::KEYWORD_PROCEDURE	= "procedure";

Token& Token::operator=(const Token& element) {
	content = element.content;
	type = element.type;
	return *this;
}

Token::Token(string content, Type type) : content(content), type(type) {}