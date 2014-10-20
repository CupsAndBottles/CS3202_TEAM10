#pragma once

#include <iostream>
#include <vector>
#include "Token.h"

using namespace std;

class Tokenizer {
public:
	static vector<Token> tokenize(string);
};