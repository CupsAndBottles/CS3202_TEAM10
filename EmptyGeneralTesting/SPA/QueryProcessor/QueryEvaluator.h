#pragma once
#include "QueryData.h"
#include <list>

using namespace std;

class QueryEvaluator
{
private:
	vector<string> EvaluateSelect(SelectClause);
	bool EvaluateParent(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateFollows(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateModifies(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateUses(SelectClause, SuchThatClause, vector<string>&);
	bool EvaluatePattern(PatternClause, vector<string>&);

	list<string> MergeResult(vector<string>, vector<string>, vector<string>);
	list<string> MergeResult(vector<string>, vector<string>);

	string ToString(int);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

