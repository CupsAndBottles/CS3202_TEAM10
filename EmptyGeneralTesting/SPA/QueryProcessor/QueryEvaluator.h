#pragma once
#include "QueryData.h"
#include "PatternMatcher.h"
#include "IntermediateResult.h"
#include <vector>
#include <list>
#include "optimizer.h"

using namespace std;

class QueryEvaluator
{
	friend class QueryEvaluatorTest;

protected:

	IntermediateResult intermediateResult;

	//Evaluate Relationship
	bool EvaluateModifies(SuchThatClause);
	bool EvaluateParent(SuchThatClause);
	bool EvaluateFollows(SuchThatClause);
	bool EvaluateCalls(SuchThatClause);
	bool EvaluateNext(SuchThatClause);
	bool EvaluateAffects(SuchThatClause);
	bool EvaluateContains(SuchThatClause);
	bool EvaluateSibling(SuchThatClause);
	bool EvaluateAffectsBip(SuchThatClause);
	bool EvaluateNextBip(SuchThatClause);

	//Evvaluate Pattern
	bool EvaluatePattern(PatternClause);

	//Evaluate With
	bool EvaluateWith(WithClause);

	vector<string> GetDataFromPKB(Synonym syn);
	string ToString(int);

	//Functions to convert between integer and string
	string ITOS(int num);
	vector<string> ITOS(vector<int> intList);
	int STOI(string s);
	vector<int> STOI(vector<string> strList);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
	void ClearIntermediateResult();
	inline void PrintIntermediateResult() { intermediateResult.Print(); }
};

