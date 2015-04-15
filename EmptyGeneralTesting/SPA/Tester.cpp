#pragma once

#include <iostream>
#include <string>
#include "Program\Program.h"
#include "QueryProcessor\QueryEvaluator.h"

using namespace std;

Pattern PatternParser(string expr) {
	Pattern patternObj = Pattern();
	bool notExactMatch = false;
	if (expr.length() != 0) {
		notExactMatch = expr.at(0) == '_';
		vector<char> resultantExpr;
		for each (char c in expr) {
			if (c != '\"' && c != '_') resultantExpr.push_back(c);
		}
		patternObj = QueryEvaluator::CreatePatternObject(string(resultantExpr.begin(), resultantExpr.end()));
	}

	return patternObj;
}

void main() {
	Program::ClearAll();
	Pattern obj = PatternParser("_\"x\"_");
}


