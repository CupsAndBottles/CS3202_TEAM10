#pragma once

#include "cppunit\config\SourcePrefix.h"
#include "TokenizerTest.h"
#include "Parser\Tokenizer.h"

#include <vector>
#include <iostream>

using namespace std;

void TokenizerTest::setUp() {};
void TokenizerTest::tearDown() {};

CPPUNIT_TEST_SUITE_REGISTRATION(TokenizerTest);

void TokenizerTest::TestSymbolTokens() {
	Token result("test", Token::Identifier);

	result = Tokenizer::tokenize(";")[0];
	CPPUNIT_ASSERT(result.content == ";");
	CPPUNIT_ASSERT(result.type == Token::EndOfStmt);

	result = Tokenizer::tokenize("{")[0];
	CPPUNIT_ASSERT(result.content == "{");
	CPPUNIT_ASSERT(result.type == Token::StartOfStmtList);

	result = Tokenizer::tokenize("}")[0];
	CPPUNIT_ASSERT(result.content == "}");
	CPPUNIT_ASSERT(result.type == Token::EndOfStmtList);

	result = Tokenizer::tokenize("(")[0];
	CPPUNIT_ASSERT(result.content == "(");
	CPPUNIT_ASSERT(result.type == Token::OpenBrace);

	result = Tokenizer::tokenize(")")[0];
	CPPUNIT_ASSERT(result.content == ")");
	CPPUNIT_ASSERT(result.type == Token::CloseBrace);

	result = Tokenizer::tokenize("+")[0];
	CPPUNIT_ASSERT(result.content == "+");
	CPPUNIT_ASSERT(result.type == Token::Plus);

	result = Tokenizer::tokenize("-")[0];
	CPPUNIT_ASSERT(result.content == "-");
	CPPUNIT_ASSERT(result.type == Token::Minus);

	result = Tokenizer::tokenize("*")[0];
	CPPUNIT_ASSERT(result.content == "*");
	CPPUNIT_ASSERT(result.type == Token::Multiply);

	result = Tokenizer::tokenize("=")[0];
	CPPUNIT_ASSERT(result.content == "=");
	CPPUNIT_ASSERT(result.type == Token::Assign);
};

void TokenizerTest::TestKeywordTokens() {
	Token result("test", Token::Identifier);

	result = Tokenizer::tokenize("call")[0];
	CPPUNIT_ASSERT(result.content == "call");
	CPPUNIT_ASSERT(result.type == Token::Call);

	result = Tokenizer::tokenize("while")[0];
	CPPUNIT_ASSERT(result.content == "while");
	CPPUNIT_ASSERT(result.type == Token::While);

	result = Tokenizer::tokenize("if")[0];
	CPPUNIT_ASSERT(result.content == "if");
	CPPUNIT_ASSERT(result.type == Token::If);

	result = Tokenizer::tokenize("then")[0];
	CPPUNIT_ASSERT(result.content == "then");
	CPPUNIT_ASSERT(result.type == Token::Then);

	result = Tokenizer::tokenize("else")[0];
	CPPUNIT_ASSERT(result.content == "else");
	CPPUNIT_ASSERT(result.type == Token::Else);

	result = Tokenizer::tokenize("procedure")[0];
	CPPUNIT_ASSERT(result.content == "procedure");
	CPPUNIT_ASSERT(result.type == Token::Procedure);
	
};

void TokenizerTest::TestNumberTokens() {
	Token result("test", Token::Identifier);

	//result = Tokenizer::tokenize("0")[0];
	//CPPUNIT_ASSERT(result.content == "0");
	//CPPUNIT_ASSERT(result.type == Token::Number);

	result = Tokenizer::tokenize("9374")[0];
	CPPUNIT_ASSERT(result.content == "9374");
	CPPUNIT_ASSERT(result.type == Token::Number);

	//result = Tokenizer::tokenize("0000")[0];
	//CPPUNIT_ASSERT(result.content == "0");
	//CPPUNIT_ASSERT(result.type == Token::Number);

	result = Tokenizer::tokenize("1000000")[0];
	CPPUNIT_ASSERT(result.content == "1000000");
	CPPUNIT_ASSERT(result.type == Token::Number);

	//result = Tokenizer::tokenize("0001239")[0];
	//CPPUNIT_ASSERT(result.content == "1239");
	//CPPUNIT_ASSERT(result.type == Token::Number);
	
};

void TokenizerTest::TestWordTokens() {
	Token result("test", Token::Identifier);

	result = Tokenizer::tokenize("x")[0];
	CPPUNIT_ASSERT(result.content == "x");
	CPPUNIT_ASSERT(result.type == Token::Identifier);

	result = Tokenizer::tokenize("word")[0];
	CPPUNIT_ASSERT(result.content == "word");
	CPPUNIT_ASSERT(result.type == Token::Identifier);

	result = Tokenizer::tokenize("p9000")[0];
	CPPUNIT_ASSERT(result.content == "p9000");
	CPPUNIT_ASSERT(result.type == Token::Identifier);

	result = Tokenizer::tokenize("superMan")[0];
	CPPUNIT_ASSERT(result.content == "superMan");
	CPPUNIT_ASSERT(result.type == Token::Identifier);

};

void TokenizerTest::TestMixedTokens() {
	vector<Token> result;

	result = Tokenizer::tokenize("x = y;");
	CPPUNIT_ASSERT(result[0].content == "x");
	CPPUNIT_ASSERT(result[1].content == "=");
	CPPUNIT_ASSERT(result[2].content == "y");
	CPPUNIT_ASSERT(result[3].content == ";");
	CPPUNIT_ASSERT(result[0].type == Token::Identifier);
	CPPUNIT_ASSERT(result[1].type == Token::Assign);
	CPPUNIT_ASSERT(result[2].type == Token::Identifier);
	CPPUNIT_ASSERT(result[3].type == Token::EndOfStmt);

};