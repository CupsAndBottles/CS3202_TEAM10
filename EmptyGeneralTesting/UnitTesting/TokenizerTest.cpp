#pragma once

#include "TokenizerTest.h"
#include "cppunit/config/SourcePrefix.h"
#include "Tokenizer.h"
#include <vector>
#include <iostream>

using namespace std;

void setUp() {};
void tearDown() {};

CPPUNIT_TEST_SUITE_REGISTRATION(TokenizerTest);

void TestSymbolTokens() {
	Token result;

	result = Tokenizer::tokenize(";")[0];
	CPPUNIT_ASSERT(result.GetContent() == ";");
	CPPUNIT_ASSERT(result.GetType() == Token::EndOfStmt);

	result = Tokenizer::tokenize("{")[0];
	CPPUNIT_ASSERT(result.GetContent() == "{");
	CPPUNIT_ASSERT(result.GetType() == Token::StartOfStmtList);

	result = Tokenizer::tokenize("}")[0];
	CPPUNIT_ASSERT(result.GetContent() == "}");
	CPPUNIT_ASSERT(result.GetType() == Token::EndOfStmtList);

	result = Tokenizer::tokenize("(")[0];
	CPPUNIT_ASSERT(result.GetContent() == "(");
	CPPUNIT_ASSERT(result.GetType() == Token::OpenBrace);

	result = Tokenizer::tokenize(")")[0];
	CPPUNIT_ASSERT(result.GetContent() == ")");
	CPPUNIT_ASSERT(result.GetType() == Token::CloseBrace);

	result = Tokenizer::tokenize("+")[0];
	CPPUNIT_ASSERT(result.GetContent() == "+");
	CPPUNIT_ASSERT(result.GetType() == Token::Plus);

	result = Tokenizer::tokenize("-")[0];
	CPPUNIT_ASSERT(result.GetContent() == "-");
	CPPUNIT_ASSERT(result.GetType() == Token::Minus);

	result = Tokenizer::tokenize("*")[0];
	CPPUNIT_ASSERT(result.GetContent() == "*");
	CPPUNIT_ASSERT(result.GetType() == Token::Multiply);

	result = Tokenizer::tokenize("=")[0];
	CPPUNIT_ASSERT(result.GetContent() == "=");
	CPPUNIT_ASSERT(result.GetType() == Token::Assign);

	result = Tokenizer::tokenize("\n")[0];
	CPPUNIT_ASSERT(result.GetContent() == "\n");
	CPPUNIT_ASSERT(result.GetType() == Token::UnixNewline);

	result = Tokenizer::tokenize("\r\n")[0];
	CPPUNIT_ASSERT(result.GetContent() == "\r\n");
	CPPUNIT_ASSERT(result.GetType() == Token::WinNewline);

};

void TestKeywordTokens() {
	Token result;

	result = Tokenizer::tokenize("call")[0];
	CPPUNIT_ASSERT(result.GetContent() == "call");
	CPPUNIT_ASSERT(result.GetType() == Token::Call);

	result = Tokenizer::tokenize("while")[0];
	CPPUNIT_ASSERT(result.GetContent() == "while");
	CPPUNIT_ASSERT(result.GetType() == Token::While);

	result = Tokenizer::tokenize("if")[0];
	CPPUNIT_ASSERT(result.GetContent() == "if");
	CPPUNIT_ASSERT(result.GetType() == Token::If);

	result = Tokenizer::tokenize("then")[0];
	CPPUNIT_ASSERT(result.GetContent() == "then");
	CPPUNIT_ASSERT(result.GetType() == Token::Then);

	result = Tokenizer::tokenize("else")[0];
	CPPUNIT_ASSERT(result.GetContent() == "else");
	CPPUNIT_ASSERT(result.GetType() == Token::Else);

};

void TestNumberTokens() {
	Token result;

	result = Tokenizer::tokenize("0")[0];
	CPPUNIT_ASSERT(result.GetContent() == "0");
	CPPUNIT_ASSERT(result.GetType() == Token::Number);

	result = Tokenizer::tokenize("9374")[0];
	CPPUNIT_ASSERT(result.GetContent() == "9374");
	CPPUNIT_ASSERT(result.GetType() == Token::Number);

	result = Tokenizer::tokenize("0000")[0];
	CPPUNIT_ASSERT(result.GetContent() == "0");
	CPPUNIT_ASSERT(result.GetType() == Token::Number);

	result = Tokenizer::tokenize("1000000")[0];
	CPPUNIT_ASSERT(result.GetContent() == "1000000");
	CPPUNIT_ASSERT(result.GetType() == Token::Number);

	result = Tokenizer::tokenize("0001239")[0];
	CPPUNIT_ASSERT(result.GetContent() == "1239");
	CPPUNIT_ASSERT(result.GetType() == Token::Number);

};

void TestWordTokens() {
	Token result;

	result = Tokenizer::tokenize("x")[0];
	CPPUNIT_ASSERT(result.GetContent() == "x");
	CPPUNIT_ASSERT(result.GetType() == Token::Identifier);

	result = Tokenizer::tokenize("word")[0];
	CPPUNIT_ASSERT(result.GetContent() == "word");
	CPPUNIT_ASSERT(result.GetType() == Token::Identifier);

	result = Tokenizer::tokenize("p9000")[0];
	CPPUNIT_ASSERT(result.GetContent() == "p9000");
	CPPUNIT_ASSERT(result.GetType() == Token::Identifier);

	result = Tokenizer::tokenize("!@asd")[0];
	CPPUNIT_ASSERT(result.GetContent() == "!@asd");
	CPPUNIT_ASSERT(result.GetType() == Token::Identifier);

};

void TestMixedTokens() {
	vector<Token> result;

	result = Tokenizer::tokenize("x = y;");
	CPPUNIT_ASSERT(result[0].GetContent() == "x");
	CPPUNIT_ASSERT(result[1].GetContent() == "=");
	CPPUNIT_ASSERT(result[2].GetContent() == "y");
	CPPUNIT_ASSERT(result[3].GetContent() == ";");
	CPPUNIT_ASSERT(result[0].GetType() == Token::Identifier);
	CPPUNIT_ASSERT(result[1].GetType() == Token::Assign);
	CPPUNIT_ASSERT(result[2].GetType() == Token::Identifier);
	CPPUNIT_ASSERT(result[3].GetType() == Token::EndOfStmt);
};


