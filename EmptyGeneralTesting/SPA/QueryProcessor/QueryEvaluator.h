#pragma once
#include "QueryData.h"
#include <list>

using namespace std;

class QueryEvaluator
{
private:
	vector<vector<Synonym>> checkModifies(SuchThatClause, vector<SelectClause>, vector<Declaration>);
	vector<vector<Synonym>> checkUses(SuchThatClause, vector<SelectClause>, vector<Declaration>);
	
	Synonym convertIntToSynonym(int, SynonymType);
	vector<vector<int>> getAllPossibleResult(vector<SelectClause>);

	vector<string> EvaluateSelect(SelectClause);
	bool EvaluateParent(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	bool EvaluateFollows(vector<Declaration>, SelectClause, SuchThatClause, vector<string>&);
	list<string> MergeResult(vector<string>, vector<string>, vector<string>);
	list<string> MergeResult(vector<string>, vector<string>);

	string ToString(int);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

