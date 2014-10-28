#pragma once

#include "Token.h"

#include <vector>

using namespace std;

class Parser {
public:
	static int Parse(string);
private:
	static int Parse(vector<Token>);

};
