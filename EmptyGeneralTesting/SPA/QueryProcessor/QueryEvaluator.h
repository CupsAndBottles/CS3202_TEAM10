#pragma once
#include "QueryData.h"
#include <list>
#include "PatternMatcher.h"

using namespace std;

class QueryEvaluator
{
	friend class QueryEvaluatorTest;

protected:
	vector<string> EvaluateSelect(SelectClause);
	bool EvaluateParent(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateFollows(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateModifies(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateUses(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluatePattern(SelectClause, PatternClause, vector<string>&);

	list<string> MergeResult(vector<string>, vector<string>, vector<string>);
	list<string> MergeResult(vector<string>, vector<string>);

	string ToString(int);
	Pattern CreatePatternObject(string);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

