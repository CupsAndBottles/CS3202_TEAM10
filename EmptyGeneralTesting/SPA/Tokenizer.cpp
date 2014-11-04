#pragma once

#include "Tokenizer.h"
#include "Token.h"

#include <string>

using namespace std;

const char Tokenizer::COMMENT_DELINEATOR = '/';

// splits a source string into tokens
// classifies tokens by type
// collapses integers e.g. 00123 => 123
vector<Token> Tokenizer::tokenize(string source) {
	vector<Token> tokens;
	string integer = "";
	string alphaString = "";

	for (unsigned int pos = 0; pos < source.length(); pos++) { // loop through string
		char currentChar = source[pos];


		if (currentChar >= 48 && currentChar <= 57) { // integer
			if (alphaString == "") {
				integer.push_back(currentChar);
			} else {
				alphaString.push_back(currentChar);
			}
		} else if ((currentChar >= 65 && currentChar <= 90) ||
				   (currentChar >= 97 && currentChar <= 122)) { // alpha
			if (integer != "") {
				throw (string) "Invalid idenitifier.";
			} else {
				alphaString.push_back(currentChar);
			}

		} else { // symbol, whitespace or endline
			if (integer != "") { // previous substring is integer
				tokens.push_back(Token(integer, Token::Number));
				integer = "";
			} else if (alphaString != "") { // previous substring is... string
				Token::Type type = stringToToken(alphaString);
				if (type == Token::Nontoken) {
					tokens.push_back(Token(alphaString, Token::Identifier));
				} else {
					tokens.push_back(Token(alphaString, type));
				}
				alphaString = "";
			}

			if (currentChar == '	' || currentChar == '\r' || currentChar == '\n' || currentChar == ' ') {
				// if space or tab or newline, skip
				continue;
			} else if (currentChar == COMMENT_DELINEATOR) {
				if (source[pos + 1] != COMMENT_DELINEATOR) { // double slashes is comment
					throw(string) "Syntax error.";
				} else {
					while (source[pos] != '\n') { // ignore chars until new line
						pos++;
					}
				}
			} else {
				string charString(1, currentChar);
				Token::Type type = stringToToken(charString);
				if (type == Token::Nontoken) {
					throw(string) "Invalid character encountered.";
				} else {
					tokens.push_back(Token(charString, type));
				}
			}
		}
	}

	// in case string is not terminated by endl
	// might also just append endl to source string
	if (integer != "") { // previous substring is integer
		tokens.push_back(Token(integer, Token::Number));
	} else if (alphaString != "") { // previous substring is... string
		Token::Type type = stringToToken(alphaString);
		if (type == Token::Nontoken) {
			tokens.push_back(Token(alphaString, Token::Identifier));
		} else {
			tokens.push_back(Token(alphaString, type));
		}
	}

	return tokens;
}

Token::Type Tokenizer::stringToToken(string str) {
	if (str == Token::START_OF_STMT_LIST) {
		return Token::StartOfStmtList;
	} else if (str == Token::END_OF_STMT_LIST) {
		return Token::EndOfStmtList;
	} else if (str == Token::OPEN_BRACE) {
		return Token::OpenBrace;
	} else if (str == Token::CLOSE_BRACE) {
		return Token::CloseBrace;
	} else if (str == Token::END_OF_STMT) {
		return Token::EndOfStmt;
	} else if (str == Token::OPERATOR_PLUS) {
		return Token::Plus;
	} else if (str == Token::OPERATOR_MINUS) {
		return Token::Minus;
	} else if (str == Token::OPERATOR_MULTIPLY) {
		return Token::Multiply;
	} else if (str == Token::OPERATOR_ASSIGN) {
		return Token::Assign;
	} else if (str == Token::KEYWORD_CALL) {
		return Token::Call;
	} else if (str == Token::KEYWORD_WHILE) {
		return Token::While;
	} else if (str == Token::KEYWORD_IF) {
		return Token::If;
	} else if (str == Token::KEYWORD_THEN) {
		return Token::Then;
	} else if (str == Token::KEYWORD_ELSE) {
		return Token::Else;
	} else if (str == Token::KEYWORD_PROCEDURE) {
		return Token::Procedure;
	} else {
		return Token::Nontoken;
	}
}