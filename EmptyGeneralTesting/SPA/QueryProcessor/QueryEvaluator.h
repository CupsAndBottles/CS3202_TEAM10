#pragma once
#include "QueryData.h"
#include <list>
#include "PatternMatcher.h"

using namespace std;

class QueryEvaluator
{
	friend class QueryEvaluatorTest;

protected:

	struct IntermediateResult {
		Synonym synonym;
		vector<int> resultInt;
		vector<string> resultVar;

		IntermediateResult(Synonym s) : synonym(s) , resultInt(), resultVar() {}
	};

	bool EvaluateModifies(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluateParent(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluateFollows(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluatePattern(PatternClause, vector<IntermediateResult>&);

	string ToString(int);
	Pattern CreatePatternObject(string);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

