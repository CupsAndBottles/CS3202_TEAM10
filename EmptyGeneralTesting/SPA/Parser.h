#pragma once

#include <iostream>;
#include <vector>;
#include "Token.h";

using namespace std;

class Parser {
public:
	int Parse(string);
private:
	int Parse(vector<Token>);
};

