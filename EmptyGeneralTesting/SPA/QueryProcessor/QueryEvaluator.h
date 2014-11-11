#pragma once
#include "QueryData.h"
#include <list>

using namespace std;

class QueryEvaluator
{
private:
	vector<string> checkModifies(SuchThatClause, SelectClause, vector<Declaration>, vector<string>);
	vector<string> checkUses(SuchThatClause, SelectClause, vector<Declaration>, vector<string>);
	
	string convertIntToString(int, SynonymType);
	vector<int> getAllPossibleResult(SelectClause);

	vector<string> EvaluateSelect(SelectClause);
	bool EvaluateParent(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateFollows(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateModifies(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateUses(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	list<string> MergeResult(vector<string>, vector<string>, vector<string>);
	list<string> MergeResult(vector<string>, vector<string>);

	string ToString(int);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

