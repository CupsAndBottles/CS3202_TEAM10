#pragma once
#include "QueryData.h"
#include "PatternMatcher.h"
#include "Answers.h"
#include <vector>
#include <list>

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

	vector<list<Answers>> answers;
	vector<pair<Synonym,int>> maps; //record index of synonym

	bool EvaluateModifies(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluateParent(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluateFollows(SuchThatClause, vector<IntermediateResult>&);
	bool EvaluatePattern(PatternClause, vector<IntermediateResult>&);

	void initiateAll(vector<Declaration>);//initiate all answers.
	void deleteAnswer(Answers*);

	string ToString(int);
	Pattern CreatePatternObject(string);

public:
	QueryEvaluator(void);
	bool EvaluateQuery(QueryData, list<string>&);
};

