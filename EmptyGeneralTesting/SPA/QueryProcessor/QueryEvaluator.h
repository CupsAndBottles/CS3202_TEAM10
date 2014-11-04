#pragma once
#include "QueryData.h"

using namespace std;

class QueryEvaluator
{
private:
	std::vector<std::vector<Synonym>> checkModifies(SuchThatClause,std::vector<SelectClause>,vector<Declaration>);
	std::vector<std::vector<Synonym>> mergeResult(std::vector<Synonym>);//will have more parameters

public:
	QueryEvaluator(void);
	std::vector<Synonym> QueryEvaluator::evaluateQuery(QueryData queryData);
};

