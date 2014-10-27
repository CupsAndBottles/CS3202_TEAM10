#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Parser.h"
#include "PKB.h"
#include "TNode.h"
#include "Tokenizer.h"

int Parse (string source) {
	vector<Token> tokens = Tokenizer::tokenize(source);
	return Parse(tokens);
}

int Parse(vector<Token> tokens) {


	return 0;
}