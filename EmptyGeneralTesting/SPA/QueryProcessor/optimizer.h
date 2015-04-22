#include "QueryData.h"
#include "Grammar.h"
#include <iostream>


using namespace std;

class Optimizer
{
private:
	int weightWith(WithClause wc);
	int weightSuchThat(SuchThatClause sc);
	int weightPattern(PatternClause pc);
	int weightStars(Argument arg1,Argument arg2);

	int numOfCon;
	int numOfProgLine;
	int numOfStmt;
	int numOfProc;
	int numOfVar;
	int numOfIf;
	int numOfWhile;
	int numOfAssign;
	int numOfModifies;
	int numOfCall;
	int numOfNext;
	int numOfFollows;
	int numOfParent;
	int numOfUses;

public:
	Optimizer();
	vector<pair<ClauseType,int>> optimize(QueryData qd);
};