#pragma once
#include "QueryData.h"

using namespace std;

class QueryEvaluator
{
private:
	vector<vector<Synonym>> checkModifies(SuchThatClause, vector<SelectClause>, vector<Declaration>);
	vector<vector<Synonym>> checkUses(SuchThatClause, vector<SelectClause>, vector<Declaration>);
	vector<vector<Synonym>> mergeResult(vector<vector<Synonym>>);//will have more parameters
	Synonym convertIntToSynonym(int, SynonymType);
	vector<vector<int>> getAllPossibleResult(vector<SelectClause>);

public:
	QueryEvaluator(void);
	vector<vector<Synonym>> QueryEvaluator::evaluateQuery(QueryData queryData);
};

