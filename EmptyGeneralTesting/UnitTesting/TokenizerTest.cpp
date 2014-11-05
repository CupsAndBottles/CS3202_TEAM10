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
	Token result("test", Token::IDENTIFIER);

	result = Tokenizer::tokenize(";")[0];
	CPPUNIT_ASSERT(result.content == ";");
	CPPUNIT_ASSERT(result.type == Token::END_OF_STMT);

	result = Tokenizer::tokenize("{")[0];
	CPPUNIT_ASSERT(result.content == "{");
	CPPUNIT_ASSERT(result.type == Token::START_OF_STMT_LIST);

	result = Tokenizer::tokenize("}")[0];
	CPPUNIT_ASSERT(result.content == "}");
	CPPUNIT_ASSERT(result.type == Token::END_OF_STMT_LIST);

	result = Tokenizer::tokenize("+")[0];
	CPPUNIT_ASSERT(result.content == "+");
	CPPUNIT_ASSERT(result.type == Token::PLUS);

	result = Tokenizer::tokenize("=")[0];
	CPPUNIT_ASSERT(result.content == "=");
	CPPUNIT_ASSERT(result.type == Token::ASSIGN);
};

void TokenizerTest::TestKeywordTokens() {
	Token result("test", Token::IDENTIFIER);

	result = Tokenizer::tokenize("while")[0];
	CPPUNIT_ASSERT(result.content == "while");
	CPPUNIT_ASSERT(result.type == Token::WHILE);

	result = Tokenizer::tokenize("procedure")[0];
	CPPUNIT_ASSERT(result.content == "procedure");
	CPPUNIT_ASSERT(result.type == Token::PROCEDURE);
	
};

void TokenizerTest::TestNumberTokens() {
	Token result("test", Token::IDENTIFIER);

	result = Tokenizer::tokenize("0")[0];
	CPPUNIT_ASSERT(result.content == "0");
	CPPUNIT_ASSERT(result.type == Token::NUMBER);

	result = Tokenizer::tokenize("9374")[0];
	CPPUNIT_ASSERT(result.content == "9374");
	CPPUNIT_ASSERT(result.type == Token::NUMBER);

	result = Tokenizer::tokenize("0000")[0];
	CPPUNIT_ASSERT(result.content == "0");
	CPPUNIT_ASSERT(result.type == Token::NUMBER);

	result = Tokenizer::tokenize("1000000")[0];
	CPPUNIT_ASSERT(result.content == "1000000");
	CPPUNIT_ASSERT(result.type == Token::NUMBER);

	result = Tokenizer::tokenize("0001239")[0];
	CPPUNIT_ASSERT(result.content == "1239");
	CPPUNIT_ASSERT(result.type == Token::NUMBER);
	
};

void TokenizerTest::TestWordTokens() {
	Token result("test", Token::IDENTIFIER);

	result = Tokenizer::tokenize("x")[0];
	CPPUNIT_ASSERT(result.content == "x");
	CPPUNIT_ASSERT(result.type == Token::IDENTIFIER);

	result = Tokenizer::tokenize("word")[0];
	CPPUNIT_ASSERT(result.content == "word");
	CPPUNIT_ASSERT(result.type == Token::IDENTIFIER);

	result = Tokenizer::tokenize("p9000")[0];
	CPPUNIT_ASSERT(result.content == "p9000");
	CPPUNIT_ASSERT(result.type == Token::IDENTIFIER);

	result = Tokenizer::tokenize("superMan")[0];
	CPPUNIT_ASSERT(result.content == "superMan");
	CPPUNIT_ASSERT(result.type == Token::IDENTIFIER);

};

void TokenizerTest::TestMixedTokens() {
	vector<Token> result;

	result = Tokenizer::tokenize("x = y;");
	CPPUNIT_ASSERT(result[0].content == "x");
	CPPUNIT_ASSERT(result[1].content == "=");
	CPPUNIT_ASSERT(result[2].content == "y");
	CPPUNIT_ASSERT(result[3].content == ";");
	CPPUNIT_ASSERT(result[0].type == Token::IDENTIFIER);
	CPPUNIT_ASSERT(result[1].type == Token::ASSIGN);
	CPPUNIT_ASSERT(result[2].type == Token::IDENTIFIER);
	CPPUNIT_ASSERT(result[3].type == Token::END_OF_STMT);

};