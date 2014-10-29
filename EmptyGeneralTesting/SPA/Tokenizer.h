#pragma once

#include "Token.h"

#include <vector>

class Tokenizer {
public:
	static vector<Token> tokenize(string);
private:
	static Token::Type stringToToken(string);
};