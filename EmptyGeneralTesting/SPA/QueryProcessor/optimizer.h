#include "QueryData.h"
#include "Grammar.h"


using namespace std;

class Optimizer
{
private:
	int weightWith(WithClause wc);
	int weightSuchThat(SuchThatClause sc);
	int weightPattern(PatternClause pc);

	int numOfCon;
	int numOfProgLine;
	int numOfStmt;
	int numOfProc;
	int numOfVar;
	int numOfIf;
	int numOfWhile;
	int numOfModifies;
	int numOfModifiesT;
	int numOfCall;
	int numOfCallT;
	int numOfNext;
	int numOfNextT;
	int numOfFollows;
	int numOfFollowsT;
	int numOfParent;
	int numOfParentT;
	int numOfUses;
	int numOfUsesT;
	int numOfAffects;

public:
	Optimizer();
};